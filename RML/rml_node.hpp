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
	 * Indentation Types
     */
    enum class IndentType
    {
        Unknown,
        Space,
        Tab
    };

    /**
	 * Interface for RMLNodes.
     */
    struct RMLNode
    {
        /**
		 * Virtual default destructor
         */
        virtual ~RMLNode() {}

        /**
		 * Writes the indentation for each line, if necessary for the indentation specification.
         */
		static void writeIndent(std::stringstream& output, IndentType indent, size_t indent_count, size_t depth);
        
        /**
		 * Writes the ending character for each line, if necessary for the indentation specification.
         */
        static void writeEnding(std::stringstream& output, IndentType indent);

		/**
		* Writes the Html node out to the given output string stream using the given indentation specification.
		*/
		virtual void write(std::stringstream& output, IndentType indent, size_t indent_count, size_t depth) = 0;
    };

	/**
	 * Abstract implementation that provides children.
	 */
	struct RMLChildrenNode : public RMLNode
	{
		std::list<std::shared_ptr<RMLNode>> children;
		void addChild(std::shared_ptr<RMLNode> child);
	};

    /**
	 * Implementation for arbitrary text in the RML file.
     */
    struct RMLTextNode : public RMLNode
    {
        std::string content;

		virtual void write(std::stringstream& output, IndentType indent, size_t indent_count, size_t depth) override;
    };

    /**
	 * Implementation for all html nodes.
     */
	struct RMLHtmlNode : public RMLChildrenNode
    {
        /**
		 * Default constructors
         */
        RMLHtmlNode() {}
        
        /**
		 * Constructor which sets the tag of the HtmlNode.
         */
        RMLHtmlNode(std::string tag) : name(tag) {}

        std::string name;
        std::string id;
        std::vector<std::string> classes;
        std::map<std::string, std::string> attrs;

		virtual void write(std::stringstream& output, IndentType indent, size_t indent_count, size_t depth) override;
    };

	/**
	 * Implementation for html comments.
	 */
	struct RMLCommentNode : public RMLChildrenNode
    {
        std::string content;

		virtual void write(std::stringstream& output, IndentType indent, size_t indent_count, size_t depth) override;
    };

}
