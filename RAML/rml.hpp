// This file is part of RML
// RML is licensed with the MIT License. See the LICENSE file for more information.

#pragma once

#include <string>
#include <list>
#include <memory>

#include "rml_node.hpp"

struct RML
{
private:

	std::list<std::shared_ptr<RMLNode>> roots;

public:

	static RML create(std::string filedata);

	RML() {}

	virtual ~RML() {}

	std::string toHtml(IndentType indent = IndentType::Space);

};