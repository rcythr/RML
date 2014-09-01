// This file is part of RML
// RML is licensed with the MIT License. See the LICENSE file for more information.

#pragma once

#include <string>
#include <list>
#include <memory>

#include <RML/rml_node.hpp>

namespace rml
{

struct RML
{
private:

	std::list<std::shared_ptr<RMLNode>> roots;
	std::map<std::string, std::shared_ptr<RMLNode>> templates;

public:

	static RML create(std::string filedata);

	RML() {}

	virtual ~RML() {}

	std::string toHtml(IndentType indent = IndentType::Space);

};

}
