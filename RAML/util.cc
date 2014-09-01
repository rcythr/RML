// This file is part of RML
// RML is licensed with the MIT License. See the LICENSE file for more information.

#include "util.hpp"

void split(std::string& data, char delim, std::vector<std::string>& out)
{
	std::string buf;
	for (char c : data)
	{
		if (c == delim)
		{
			out.push_back(buf);
			buf = "";
		}
		else
		{
			buf += c;
		}
	}
	out.push_back(buf);
}