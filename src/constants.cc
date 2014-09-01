// This file is part of RML
// RML is licensed with the MIT License. See the LICENSE file for more information.

#include <RML/constants.hpp>
#include <RML/util.hpp>

std::unordered_set<std::string> html5Tags
{
	"a",
	"abbr",
	"address",
	"area",
	"article",
	"aside",
	"audio",
	"b",
	"base",
	"bdi",
	"bdo",
	"blockquote",
	"body",
	"br",
	"button",
	"canvas",
	"caption",
	"cite",
	"code",
	"col",
	"colgroup",
	"data",
	"datalist",
	"dd",
	"del",
	"details",
	"dfn",
	"div",
	"dl",
	"dt",
	"em",
	"embed",
	"fieldset",
	"figcaption",
	"figure",
	"footer",
	"form",
	"h1",
	"h2",
	"h3",
	"h4",
	"h5",
	"h6",
	"head",
	"header",
	"hr",
	"html",
	"i",
	"iframe",
	"img",
	"input",
	"ins",
	"kbd",
	"keygen",
	"label",
	"legend",
	"li",
	"link",
	"main",
	"map",
	"mark",
	"math",
	"menu",
	"menuitem",
	"meta",
	"meter",
	"nav",
	"noscript",
	"object",
	"ol",
	"optgroup",
	"option",
	"output",
	"p",
	"param",
	"pre",
	"progress",
	"q",
	"rp",
	"rt",
	"ruby",
	"s",
	"samp",
	"script",
	"section",
	"select",
	"small",
	"source",
	"span",
	"strong",
	"style",
	"sub",
	"summary",
	"sup",
	"svg",
	"table",
	"tbody",
	"td",
	"template",
	"textarea",
	"tfoot",
	"th",
	"thead",
	"time",
	"title",
	"tr",
	"track",
	"u",
	"ul",
	"var"
	"wbr",
};

std::unordered_set<std::string> deprecatedTags
{
	"acronym",
	"applet",
	"basefont",
	"bgsound",
	"big",
	"blink",
	"center",
	"decorator",
	"dir",
	"font",
	"frame",
	"frameset",
	"hgroup",
	"isindex",
	"listing",
	"marquee",
	"nobr",
	"noframes",
	"plaintext",
	"shadow",
	"spacer",
	"strike",
	"tt",
	"xmp"
};

std::unordered_set<std::string> globalAttributes
{
	{ "accesskey",
	"class",
	"contenteditable",
	"contextmenu",
	"dir",
	"draggable",
	"dropzone",
	"hidden",
	"id",
	"itemid",
	"itemprop",
	"itemref",
	"itemscope",
	"itemtype",
	"lang",
	"spellcheck",
	"style",
	"tabindex",
	"title" }
};

std::unordered_map<std::string, std::set<std::string>> attributeValidationSets
{
	{ "a", { "download", "href", "media", "ping", "rel", "target", "datafld", "datasrc", "hreflang", "methods", "type", "urn" } },
	{ "area", { "alt", "coords", "download", "href", "hreflang", "media", "rel", "shape", "target", "type" } },
	{"audio", {"autoplay","buffered","controls","loop", "muted","played", "preload", "src","volume"}},
	{"base", {"href","target"}},
	{"blockquote", {"cite"}},
	{"body", { "onafterprint", "onbeforeprint", "onbeforeunload", "onblur", "onerror", "onfocus", "onhashchange", "onload", "onmessage", "onoffline", "ononline", "onpopstate", "onredo", "onresize", "onstorage", "onundo", "onunload" }},
	{"button", { "autofocus", "disabled", "form", "formaction", "formenctype", "formmethod", "formnovalidate", "formtarget", "name", "type", "value"}},
	{"canvas", {"width", "height"}},
	{"col", {"span"}},
	{"colgroup", {"span"}},
	{"data", {"value"}},
	{"datalist", {}},
	{"dd", {"nowrap"}},
	{"del", {"cite","datetime"}},
	{"details", {"open"}},
	{"dl", {"compact"}},
	{"embed", {"height","src","type","width"}},
	{"fieldset", {"disabled","form","name"}},
	{"form", {"accept-charset", "action", "autocomplete", "enctype", "method", "name", "novalidate", "target",}},
	{"head", { "profile" }},
	{"hr", {"color"}},
	{"html", { "manifest", "version" }},
	{"iframe", {"allowfullscreen","height","name","remote","scrolling","sandbox","seamless","src","srcdoc","width"}},
	{"img", {"alt","crossorigin","height","ismap","longdesc","src","srcset","width","usemap"}},
	{"input", {"type","accept","autocomplete","autofocus","autosave","checked","disabled","form","formaction","formenctype","formmethod","formnovalidate","formtarget","height","inputmode","list","max","maxlength","min","minlength","multiple","name","pattern","placeholder","readonly","required","selectionDirection","size","spellcheck","src","step","value","width"}},
	{"ins", {"cite","datetime"}},
	{"keygen", { "autofocus", "challenge", "disabled", "form", "keytype", "name"}},
	{"label", { "accesskey", "for", "form" }},
	{"li", {"value", "type"}},
	{"link", { "charset", "disabled", "href", "hreflang", "media", "methods", "rel", "sizes", "target", "type" }},
	{"map", {"name"}},
	{"menu",{"label","type"}},
	{"menuitem", {"checked", "command", "default", "disabled", "icon", "label", "radiogroup", "type"}},
	{"meta", { "charset", "content", "http-equiv", "name", "scheme" }},
	{"meter", { "value", "min", "max", "low", "high", "optimum", "form"}},
	{"object", {"data","form","height","name","type","usemap","width"}},
	{"ol", {"reversed", "start", "type"}},
	{"optgroup", {"disabled", "label"}},
	{"option", {"disabled","label", "selected","value"}},
	{"output", { "for", "form", "name" }},
	{"param", {"name", "value"}},
	{"pre", {"wrap"}},
	{"progress", {"max","value"}},
	{"q", {"cite"}},
	{"script", { "async", "src", "type", "language", "defer", "crossorigin" }},
	{"select", {"autofocus", "disabled", "form", "multiple", "name", "required", "size"}},
	{"source", {"src", "type"}},
	{"style", { "type", "media", "scoped", "title", "disabled" }},
	{"td", {"colspan","headers","rowspan"}},
	{"template", { "content" }},
	{"textarea", {"autocomplete","autofocus","cols","disabled","form","maxlength","minlength","name","placeholder","readonly","required","rows","selectionDirection","selectionEnd","selectionStart","spellcheck","wrap"}},
	{"th", {"colspan", "headers", "rowspan", "scope"}},
	{"time", {"datetime"}},
	{"track", {"default", "kind", "label", "src", "srclang"}},
	{"video", {"autoplay", "buffered", "controls", "crossorigin", "height", "loop", "muted", "played", "preload", "poster", "src", "width"}},
};

std::unordered_set<std::string> voidTags
{
	"base",
	"br",
	"col",
	"embed",
	"img",
	"input",
	"keygen",
	"link",
	"menuitem",
	"meta",
	"param",
	"source",
	"track",
	"wbr",
};

bool isHtml5Tag(std::string& tag)
{
	return html5Tags.find(tag) != html5Tags.end();
}

bool isDeprecatedTag(std::string& tag)
{
	return deprecatedTags.find(tag) != deprecatedTags.end();
}

bool isVoidTag(std::string& tag)
{
	return voidTags.find(tag) != voidTags.end();
}

bool isAttributeValidForTag(const std::string& tag, const std::string& attr)
{
	// Special cases
	if (tag == "svg")
		return true;
	else if (tag == "math")
		return true;
	else if (tag == "mstyle")
		return true;

	if (beginsWith(attr, "data-"))
		return true;

	// Handle global attributes
	auto glob_find = globalAttributes.find(attr);
	if(glob_find != globalAttributes.end())
		return true;

	// Handle tag specific
	auto tag_find = attributeValidationSets.find(tag);
	if (tag_find != attributeValidationSets.end())
	{
		auto attr_find = tag_find->second.find(attr);
		return attr_find != tag_find->second.end();
	}

	// With an invalid tag there are no valid attributes.
	return false;
}
