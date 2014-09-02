// This file is part of RML
// RML is licensed with the MIT License. See the LICENSE file for more information.

#include <RML/rml_node.hpp>

#include <RML/constants.hpp>

#include <iostream>

using namespace rml;

void RMLTextNode::write(std::stringstream& output, IndentType indent, size_t depth)
{
	writeIndent(output, indent, depth);
	output << content;
	writeEnding(output, indent);
}

void RMLHtmlNode::write(std::stringstream& output, IndentType indent, size_t depth)
{
	writeIndent(output, indent, depth);
	output << '<' << name;

	// Add the ID attribute, if applicable
	if (id != "")
	{
		output << " id=\"" << id << "\"";
	}

	// Construct and add the class attribute, if applicable.
	if (classes.size() > 0)
	{
		std::string sep = "";
		output << " class=\"";

		for (auto& name : classes)
		{
			output << sep << name;
			sep = " ";
		}

		output << "\"";
	}

	// Add all other attributes.
	for (const auto& attr : attrs)
	{
		if (!isAttributeValidForTag(name, attr.first))
		{
			std::cerr << "Warning! The attribute '" << attr.first << "' is not valid for tag '" << name << "' by the HTML5 specification. It may be deprecated, bad style, or otherwise wrong. " << std::endl;
		}

		if (attr.second.size() == 0)
		{
			output << ' ' << attr.first;
		}
		else
		{
			output << ' ' << attr.first << "=\"" << attr.second << "\"";
		}
	}

	bool voidTag = isVoidTag(name);

	if (voidTag && children.size() > 0)
	{
		std::cerr << "Warning! The tag '" << name << "' contains children, but is not allowed to by the HTML5 specification." << std::endl;
	}

	if (voidTag && children.size() == 0)
	{
		output << " />";
		writeEnding(output, indent);
	}
	else
	{
		output << '>';
		writeEnding(output, indent);

		for (const auto& child : children)
		{
			child->write(output, indent, depth + 1);
		}

		writeIndent(output, indent, depth);
		output << "</" << name << '>';
		writeEnding(output, indent);
	}
}

void RMLHtmlNode::addChild(std::shared_ptr<RMLNode> child)
{
	children.push_back(child);
}

void RMLCommentNode::write(std::stringstream& output, IndentType indent, size_t depth)
{
    writeIndent(output, indent, depth);
    output << "<!-- " << content;

    if(children.size() > 0)
    {
        writeEnding(output, indent);
        for(const auto& child : children)
        {
            child->write(output, indent, depth + 1);
        }
    }

    writeIndent(output, indent, depth);
    output << "-->";
    writeEnding(output, indent);
}

void RMLCommentNode::addChild(std::shared_ptr<RMLNode> child)
{
    children.push_back(child);    
}

void RMLNode::writeIndent(std::stringstream& output, IndentType indent, size_t depth)
{
	for (size_t i = 0; i < depth; ++i)
	{
		switch (indent)
		{
		case IndentType::Unknown:
			break;
		case IndentType::Space:
			output << "    ";
			break;
		case IndentType::Tab:
			output << '\t';
			break;
		}
	}
}

void RMLNode::writeEnding(std::stringstream& output, IndentType indent)
{
	if (indent != IndentType::Unknown)
		output << std::endl;
}
