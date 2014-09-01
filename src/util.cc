// This file is part of RML
// RML is licensed with the MIT License. See the LICENSE file for more information.

#include <RML/util.hpp>

namespace rml
{

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

bool beginsWith(const std::string& data, std::string substr)
{
	// Trivial case
	if (substr.length() > data.length())
		return false;

	for (size_t i = 0; i < substr.length(); ++i)
	{
		if (data[i] != substr[i])
			return false;
	}

	return true;
}

}
