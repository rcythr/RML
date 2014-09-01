// This file is part of RML
// RML is licensed with the MIT License. See the LICENSE file for more information.

#pragma once

#include <string>
#include <vector>

void split(std::string& data, char delim, std::vector<std::string>& out);

bool beginsWith(const std::string& data, std::string substr);