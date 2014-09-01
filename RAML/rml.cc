// This file is part of RML
// RML is licensed with the MIT License. See the LICENSE file for more information.

#include "rml.hpp"
#include "util.hpp"
#include "constants.h"

#include <functional>
#include <iostream>

struct Node
{
	Node(size_t lineno, size_t depth, std::string content) : lineno(lineno), depth(depth), content(content) {}

	size_t lineno;
	size_t depth;
	std::string content;
	std::vector<std::shared_ptr<Node>> children;
};

enum class LineParseState
{
	Text,

	Tag,
	Class,
	Id,
	AttrKey,
	AttrKeyEndWs,
	AttrValue,
	AttrValueNoEsc,
	AttrValueSingle,
	AttrValueSingleEsc,
	AttrValueDouble,
	AttrValueDoubleEsc,
	EndAttr
};


std::vector<std::string> toLines(std::string& data)
{
	std::vector<std::string> lines;
	split(data, '\n', lines);
	return lines;
}

std::vector<std::tuple<size_t, std::string>> countIndents(std::vector<std::string> lines)
{
	std::vector<std::tuple<size_t, std::string>> result;
	
	IndentType indentType = IndentType::Unknown;
	size_t depth = 0;

	size_t lineno = 0;
	for (auto& line : lines)
	{
		bool foundNonIndent = false;
		size_t count = 0;
		for (char c : line)
		{
			switch (c)
			{
			case ' ':
				switch (indentType)
				{
				case IndentType::Unknown:
					indentType = IndentType::Space;
				case IndentType::Space:
					++count;
					break;
				case IndentType::Tab:
					throw std::runtime_error(std::string("Inconsistent use of tabs and spaces. See line #") + std::to_string(lineno));
				}
				break;
			case '\t':
				switch (indentType)
				{
				case IndentType::Unknown:
					indentType = IndentType::Space;
				case IndentType::Tab:
					++count;
					break;
				case IndentType::Space:
					throw std::runtime_error(std::string("Inconsistent use of tabs and spaces. See line #") + std::to_string(lineno));
				}
				break;
			default:
				foundNonIndent = true;
				break;
			}

			if (foundNonIndent)
			{
				if (depth == 0)
				{
					depth = count;
				}
				break;
			}
				
		}

		if (depth != 0)
		{
			if (count % depth != 0)
			{
				throw std::runtime_error(std::string("Inconsistent number of spaces per indent level. See line #") + std::to_string(lineno));
			}

			result.push_back(std::tuple<size_t, std::string>(count/depth, line.substr(count)));
		}
		else
		{
			result.push_back(std::tuple<size_t, std::string>(count, line.substr(count)));
		}
		

		++lineno;
	}
	
	return result;
}

std::shared_ptr<Node> toNodeTreeRec(std::vector<std::tuple<size_t, std::string>>& elements, size_t& index, size_t depth)
{
	if(index < elements.size())
	{
		if (std::get<1>(elements[index]) == "")
		{
			++index;
			if (index >= elements.size())
				return nullptr;
		}

		size_t nextDepth = std::get<0>(elements[index]);
		if (nextDepth == depth)
		{
			auto node = std::make_shared<Node>(index+1, depth, std::get<1>(elements[index]));
			++index;

			auto child = toNodeTreeRec(elements, index, depth + 1);
			while (child != nullptr)
			{
				node->children.push_back(child);
				child = toNodeTreeRec(elements, index, depth + 1);
			}

			return node;
		}
		else if (nextDepth > depth) 
		{
			throw std::runtime_error(std::string("Unexpected indent on line #") + std::to_string(index + 1));
		}
	}
	return nullptr;
}

std::vector<std::shared_ptr<Node>> toNodeTree(std::vector<std::tuple<size_t, std::string>> countedIndents)
{
	std::vector<std::shared_ptr<Node>> result;

	size_t index = 0;
	while (index < countedIndents.size())
	{
		if (std::get<1>(countedIndents[index]) == "")
		{
			++index;
			continue;
		}

		if (std::get<0>(countedIndents[index]) == 0)
		{
			auto root = std::make_shared<Node>(index+1, 0, std::get<1>(countedIndents[index]));
			++index;

			auto child = toNodeTreeRec(countedIndents, index, 1);
			while (child != nullptr)
			{
				root->children.push_back(child);
				child = toNodeTreeRec(countedIndents, index, 1);
			}

			result.push_back(root);
		}
		else
		{
			throw std::runtime_error(std::string("Unexpected indent on line #") + std::to_string(index + 1));
		}
	}

	return result;
}

void handleSubNodes(std::shared_ptr<RMLHtmlNode> htmlNode, std::shared_ptr<Node> node);

std::shared_ptr<RMLNode> toRMLTree(std::shared_ptr<Node> node)
{
	std::shared_ptr<RMLHtmlNode> htmlNode = nullptr;
	std::shared_ptr<RMLTextNode> textNode = nullptr;
	std::string buffer1, buffer2;

	LineParseState state = LineParseState::Tag;
	for (char c : node->content)
	{
		switch (state)
		{
		case LineParseState::Tag:
			switch (c)
			{
			case '_':
				textNode = std::make_shared<RMLTextNode>();
				state = LineParseState::Text;
				break;
			case '#': //break;
			case '.': // break;
			case ' ':
			{
				bool html5 = isHtml5Tag(buffer1);
				bool dep = isDeprecatedTag(buffer1);

				if (html5 || dep)
				{
					if (dep)
					{
						std::cerr << "Warning: The \'" << buffer1 << "\' tag is deprecated. Consider replacing it." << std::endl;
					}

					htmlNode = std::make_shared<RMLHtmlNode>();
					htmlNode->name = buffer1;
					buffer1 = "";
					if (c == ' ')
						state = LineParseState::AttrKey;
					else if (c == '.')
						state = LineParseState::Class;
					else if (c == '#')
						state = LineParseState::Id;
				}
				else
				{
					textNode = std::make_shared<RMLTextNode>();
					buffer1 += c;
					state = LineParseState::Text;
				}
			} break;
			default:
				buffer1 += c;
			}
			break;
		case LineParseState::Text:
			buffer1 += c;
			break;
		case LineParseState::Class:
			switch (c)
			{
			case '\t': // break;
			case ' ':
				htmlNode->classes.push_back(buffer1);
				buffer1 = "";
				state = LineParseState::AttrKey;
				break;
			case '.':
				htmlNode->classes.push_back(buffer1);
				buffer1 = "";
				break;
			default:
				buffer1 += c;
			}
			break;
		case LineParseState::Id:
			switch (c)
			{
			case '\t': //break;
			case '.':
				htmlNode->id = buffer1;
				buffer1 = "";
				state = LineParseState::Class;
				break;
			case ' ':
				htmlNode->id = buffer1;
				buffer1 = "";
				state = LineParseState::AttrKey;
				break;
			default:
				buffer1 += c;
				break;
			}
			break;
		case LineParseState::AttrKey:
			switch (c)
			{
			case '\t': // break;
			case ' ':
				if (buffer1.size() > 0)
				{
					state = LineParseState::AttrKeyEndWs;
				}
				break;
			case '.':
				if (buffer1.size() > 0)
				{
					htmlNode->attrs[buffer1] = "";
					buffer1 = "";
				}
				state = LineParseState::Class;
				break;
			case '#':
				if (buffer1.size() > 0)
				{
					htmlNode->attrs[buffer1] = "";
					buffer1 = "";
				}
				state = LineParseState::Id;
				break;
			case '=':
				state = LineParseState::AttrValue;
				break;
			default:
				buffer1 += c;
				break;
			}
			break;
		case LineParseState::AttrKeyEndWs:
			switch (c)
			{
			case '\t': // break;
			case ' ':
				break;
			case '.':
				state = LineParseState::Class;
				break;
			case '#':
				state = LineParseState::Id;
				break;
			case '=':
				state = LineParseState::AttrValue;
				break;
			default:
				if (buffer1.size() > 0)
				{
					htmlNode->attrs[buffer1] = "";
					buffer1 = "";
				}

				buffer1 += c;
				state = LineParseState::AttrKey;
				break;
			}
			break;
		case LineParseState::AttrValue:
			switch (c)
			{
			case '\t': // break;
			case ' ':
				break;
			case '\'':
				if (buffer2.size() > 0)
					throw std::runtime_error(std::string("Parse error while parsing line #") + std::to_string(node->lineno));

				state = LineParseState::AttrValueSingle;
				break;
			case '\"':
				if (buffer2.size() > 0)
					throw std::runtime_error(std::string("Parse error while parsing line #") + std::to_string(node->lineno));

				state = LineParseState::AttrValueDouble;
				break;
			case '.':
				htmlNode->attrs[buffer1] = "";
				buffer1 = "";
				buffer2 = "";
				state = LineParseState::Class;
				break;
			case '#':
				htmlNode->attrs[buffer1] = "";
				buffer1 = "";
				buffer2 = "";
				state = LineParseState::Id;
				break;
			default:
				buffer2 += c;
				state = LineParseState::AttrValueNoEsc;
				break;
			}
			break;
		case LineParseState::AttrValueNoEsc:
			switch (c)
			{
			case '\t': // break;
			case ' ':
				htmlNode->attrs[buffer1] = buffer2;
				buffer1 = "";
				buffer2 = "";
				state = LineParseState::AttrKey;
				break;
			case '.':
				htmlNode->attrs[buffer1] = buffer2;
				buffer1 = "";
				buffer2 = "";
				state = LineParseState::Class;
				break;
			case '#':
				htmlNode->attrs[buffer1] = buffer2;
				buffer1 = "";
				buffer2 = "";
				state = LineParseState::Id;
				break;
			default:
				buffer2 += c;
				break;
			}
			break;
		case LineParseState::AttrValueSingle:
			switch (c)
			{
			case '\'':
				htmlNode->attrs[buffer1] = buffer2;
				buffer1 = "";
				buffer2 = "";
				state = LineParseState::EndAttr;
				break;
			case '\\':
				state = LineParseState::AttrValueSingleEsc;
				break;
			default:
				buffer2 += c;
				break;
			}
			break;
		case LineParseState::AttrValueSingleEsc:
			switch (c)
			{
			case '\\':
				buffer2 += '\\';
				break;
			case '\'':
				buffer2 += '\'';
				break;
			default:
				buffer2 += '\\';
				state = LineParseState::AttrValueSingle;
				break;
			}
			break;
		case LineParseState::AttrValueDouble:
			switch (c)
			{
			case '\"':
				htmlNode->attrs[buffer1] = buffer2;
				buffer1 = "";
				buffer2 = "";
				state = LineParseState::EndAttr;
				break;
			case '\\':
				state = LineParseState::AttrValueSingleEsc;
				break;
			default:
				buffer2 += c;
				break;
			}
			break;
		case LineParseState::AttrValueDoubleEsc:
			switch (c)
			{
			case '\\':
				buffer2 += '\\';
				break;
			case '\"':
				buffer2 += '\"';
				break;
			default:
				buffer2 += '\\';
				state = LineParseState::AttrValueDouble;
				break;
			}
			break;
		case LineParseState::EndAttr:
			switch (c)
			{
			default:
				buffer1 += c;
				//break;
			case ' ':
				state = LineParseState::AttrKey;
				break;
			case '#':
				state = LineParseState::Id;
				break;
			case '.':
				state = LineParseState::Class;
				break;
			}
			break;
		}
	}

	switch (state)
	{
	case LineParseState::Text:
		textNode->content = buffer1;
		return textNode;
	case LineParseState::Tag:
	{
		bool html5 = isHtml5Tag(buffer1);
		bool dep = isDeprecatedTag(buffer1);

		if (html5 || dep)
		{
			if (dep)
			{
				std::cerr << "Warning: The \'" << buffer1 << "\' tag is deprecated. Consider replacing it." << std::endl;
			}

			if (htmlNode == nullptr)
				htmlNode = std::make_shared<RMLHtmlNode>();

			htmlNode->name = buffer1;
			for (auto& child : node->children)
			{
				htmlNode->addChild(toRMLTree(child));
			}
			return htmlNode;
		}
		else
		{
			textNode = std::make_shared<RMLTextNode>();
			textNode->content = buffer1;
			return textNode;
		}
	}
	case LineParseState::Class:
		htmlNode->classes.push_back(buffer1);
		for (auto& child : node->children)
		{
			htmlNode->addChild(toRMLTree(child));
		}
		return htmlNode;
	case LineParseState::Id:
		htmlNode->id = buffer1;
		for (auto& child : node->children)
		{
			htmlNode->addChild(toRMLTree(child));
		}
		return htmlNode;
	case LineParseState::AttrKey:
		htmlNode->attrs[buffer1] = "";
		for (auto& child : node->children)
		{
			htmlNode->addChild(toRMLTree(child));
		}
		return htmlNode;
	case LineParseState::AttrKeyEndWs:
		htmlNode->attrs[buffer1] = "";
		for (auto& child : node->children)
		{
			htmlNode->addChild(toRMLTree(child));
		}
		return htmlNode;
	case LineParseState::AttrValue:
		htmlNode->attrs[buffer1] = "";
		for (auto& child : node->children)
		{
			htmlNode->addChild(toRMLTree(child));
		}
		return htmlNode;
	case LineParseState::AttrValueNoEsc:
		htmlNode->attrs[buffer1] = buffer2;
		for (auto& child : node->children)
		{
			htmlNode->addChild(toRMLTree(child));
		}
		return htmlNode;
	case LineParseState::EndAttr:
		for (auto& child : node->children)
		{
			htmlNode->addChild(toRMLTree(child));
		}
		return htmlNode;
	default:
		break;
	}

	throw std::runtime_error(std::string("Parse error while parsing line #") + std::to_string(node->lineno));
}

RML RML::create(std::string filedata)
{
	RML raml;

	for (auto root : toNodeTree(countIndents(toLines(filedata))))
	{
		raml.roots.push_back(toRMLTree(root));
	}

	return raml;
}

std::string RML::toHtml(IndentType indent)
{
	std::stringstream output;

	for (auto root : roots)
	{
		root->write(output, indent, 0);
	}

	return output.str();
}