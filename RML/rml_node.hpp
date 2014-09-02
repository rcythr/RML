// This file is part of RML
// RML is licensed with the MIT License. See the LICENSE file for more information.

#pragma once

#include <map>
#include <vector>
#include <list>
#include <string>
#include <memory>
#include <sstream>

namespace rml
{

    /**
     */
    enum class IndentType
    {
        Unknown,
        Space,
        Tab
    };

    /**
     */
    struct RMLNode
    {
        /**
         */
        virtual ~RMLNode() {}

        /**
         */
		static void writeIndent(std::stringstream& output, IndentType indent, size_t indent_count, size_t depth);
        
        /**
         */
        static void writeEnding(std::stringstream& output, IndentType indent);

        /**
         */
		virtual void write(std::stringstream& output, IndentType indent, size_t indent_count, size_t depth) = 0;
    };

    /**
     */
    struct RMLTextNode : public RMLNode
    {
        std::string content;

        /**
         */
		virtual void write(std::stringstream& output, IndentType indent, size_t indent_count, size_t depth) override;
    };

    /**
     */
    struct RMLHtmlNode : public RMLNode
    {
        /**
         */
        RMLHtmlNode() {}
        
        /**
         */
        RMLHtmlNode(std::string name) : name(name) {}

        std::string name;
        std::string id;
        std::vector<std::string> classes;
        std::map<std::string, std::string> attrs;
        std::list<std::shared_ptr<RMLNode>> children;

        /**
         */
		virtual void write(std::stringstream& output, IndentType indent, size_t indent_count, size_t depth) override;

        /**
         */
        void addChild(std::shared_ptr<RMLNode> child);
    };

    struct RMLCommentNode : public RMLNode
    {
        std::string content;
        std::list<std::shared_ptr<RMLNode>> children;

		virtual void write(std::stringstream& output, IndentType indent, size_t indent_count, size_t depth) override;

        void addChild(std::shared_ptr<RMLNode> child);
    };

}
