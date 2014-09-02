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
     */
    extern std::unordered_set<std::string> html5Tags;
    
    /**
     */
    extern std::unordered_set<std::string> depTags;
    
    /**
     */
    extern std::unordered_set<std::string> voidTags;
    
    /**
     */
    extern std::unordered_set<std::string> globalAttributes;
    
    /**
     */
    extern std::unordered_map<std::string, std::set<std::string>> attributeValidationSets;

    /**
     */
    bool isHtml5Tag(std::string& tag);
    
    /**
     */
    bool isDeprecatedTag(std::string& tag);
    
    /**
     */
    bool isVoidTag(std::string& tag);
    
    /**
     */
    bool isAttributeValidForTag(const std::string& tag, const std::string& attr);
}
