// This file is part of RML
// RML is licensed with the MIT License. See the LICENSE file for more information.

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>

namespace rml
{
    /**
	 * Tests if the given tag is in the set of valid html 5 tags.
     */
    bool isHtml5Tag(std::string& tag);
    
    /**
	 * Tests if the given tag is in the set of deprecated html tags.
     */
    bool isDeprecatedTag(std::string& tag);
    
    /**
	* Tests if the given tag is a tag which must not have a closing tag.
     */
    bool isVoidTag(std::string& tag);
    
    /**
	 * Tests if a given attribute is valid for a given tag.
	 * @arg tag the tag to test
	 * @arg attr the attribute to check against global attributes, tag specific attributes, and other exceptions (such as ARIA attributes).
     */
    bool isAttributeValidForTag(const std::string& tag, const std::string& attr);
}
