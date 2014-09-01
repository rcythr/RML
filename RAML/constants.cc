#include "constants.h"

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
	"menu"
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

bool isHtml5Tag(std::string& tag)
{
	return html5Tags.find(tag) != html5Tags.end();
}

bool isDeprecatedTag(std::string& tag)
{
	return deprecatedTags.find(tag) != deprecatedTags.end();
}