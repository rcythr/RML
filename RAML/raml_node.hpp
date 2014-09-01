#pragma once

#include <map>
#include <vector>
#include <list>
#include <string>
#include <memory>
#include <sstream>

enum class IndentType
{
	Unknown,
	Space,
	Tab
};

struct RAMLNode
{
	virtual ~RAMLNode() {}

	static void writeIndent(std::stringstream& output, IndentType indent, size_t depth);
	static void writeEnding(std::stringstream& output, IndentType indent);

	virtual void write(std::stringstream& output, IndentType indent, size_t depth) = 0;
};

struct RAMLTextNode : public RAMLNode
{
	std::string content;

	virtual void write(std::stringstream& output, IndentType indent, size_t depth) override;
};

struct RAMLHtmlNode : public RAMLNode
{
	RAMLHtmlNode() {}
	RAMLHtmlNode(std::string name) : name(name) {}

	std::string name;
	std::string id;
	std::vector<std::string> classes;
	std::map<std::string, std::string> attrs;
	std::list<std::shared_ptr<RAMLNode>> children;

	virtual void write(std::stringstream& output, IndentType indent, size_t depth) override;

	void addChild(std::shared_ptr<RAMLNode> child);
};

