// This file is part of RAML
// RAML is licensed with the MIT License. See the LICENSE file for more information.

#pragma once

#include <unordered_set>
#include <string>

extern std::unordered_set<std::string> html5Tags;
extern std::unordered_set<std::string> depTags;

bool isHtml5Tag(std::string& tag);
bool isDeprecatedTag(std::string& tag);