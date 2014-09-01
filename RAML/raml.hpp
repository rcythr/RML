#pragma once

#include <string>
#include <list>
#include <memory>

#include "raml_node.hpp"

struct RAML
{
private:

	std::list<std::shared_ptr<RAMLNode>> roots;

public:

	static RAML create(std::string filedata);

	RAML() {}

	virtual ~RAML() {}

	std::string toHtml(IndentType indent = IndentType::Space);

};