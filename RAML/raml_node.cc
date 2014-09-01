// This file is part of RAML
// RAML is licensed with the MIT License. See the LICENSE file for more information.

#include "raml_node.hpp"

void RAMLTextNode::write(std::stringstream& output, IndentType indent, size_t depth)
{
	writeIndent(output, indent, depth);
	output << content;
	writeEnding(output, indent);
}

void RAMLHtmlNode::write(std::stringstream& output, IndentType indent, size_t depth)
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
		if (attr.second.size() == 0)
		{
			output << ' ' << attr.first;
		}
		else
		{
			output << ' ' << attr.first << "=\"" << attr.second << "\"";
		}
	}

	output << '>';
	writeEnding(output, indent);

	for (const auto& child : children)
	{
		child->write(output, indent, depth+1);
	}

	writeIndent(output, indent, depth);
	output << "</" << name << '>';
	writeEnding(output, indent);
}

void RAMLHtmlNode::addChild(std::shared_ptr<RAMLNode> child)
{
	children.push_back(child);
}

void RAMLNode::writeIndent(std::stringstream& output, IndentType indent, size_t depth)
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

void RAMLNode::writeEnding(std::stringstream& output, IndentType indent)
{
	if (indent != IndentType::Unknown)
		output << std::endl;
}