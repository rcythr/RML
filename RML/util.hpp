// This file is part of RML
// RML is licensed with the MIT License. See the LICENSE file for more information.

#pragma once

#include <string>
#include <vector>

namespace rml
{
    /**
	 * Splits a given string on a delimeter.
	 * @arg data the input data to split
	 * @arg delim the delimeter to split on.
	 * @arg out the collection to insert the parts of the string into
     */
    void split(std::string& data, char delim, std::vector<std::string>& out);

    /**
	 * Checks if the given substring is at the start of the given data.
	 * @arg data the larger string to test against.
	 * @arg substr the substring to test with.
     */
    bool beginsWith(const std::string& data, std::string substr);

}
