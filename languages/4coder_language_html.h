/*
4coder_language_html.h - Sets up the HTML language context.
*/

// TOP

#if !defined(FCODER_LANGUAGE_HTML_H)
#define FCODER_LANGUAGE_HTML_H

#define HTML_TOKEN_TAGS CPP_TOKEN_KEY_OTHER
#define HTML_TOKEN_ARGUMENTS CPP_PP_INCLUDE

static Parse_Context_ID parse_context_language_html;

#define PSAT(s, t) {s, sizeof(s)-1, t}
static void
init_language_html(Application_Links *app){
    if (parse_context_language_html != 0) return;
    
    Parser_String_And_Type kw[] = {
        PSAT("DOCTYPE", HTML_TOKEN_TAGS),
        PSAT("abbr", HTML_TOKEN_TAGS),
        PSAT("acronym", HTML_TOKEN_TAGS),	 
        PSAT("address", HTML_TOKEN_TAGS),	 
        PSAT("a", HTML_TOKEN_TAGS),
        PSAT("applet", HTML_TOKEN_TAGS),
        PSAT("area", HTML_TOKEN_TAGS),
        PSAT("b", HTML_TOKEN_TAGS),
        PSAT("base", HTML_TOKEN_TAGS),
        PSAT("basefont", HTML_TOKEN_TAGS),
        PSAT("bdo", HTML_TOKEN_TAGS),
        PSAT("bgsound", HTML_TOKEN_TAGS),
        PSAT("big", HTML_TOKEN_TAGS),
        PSAT("blink", HTML_TOKEN_TAGS),
        PSAT("blockquote", HTML_TOKEN_TAGS),
        PSAT("body", HTML_TOKEN_TAGS),
        PSAT("br", HTML_TOKEN_TAGS),
        PSAT("button", HTML_TOKEN_TAGS),
        PSAT("caption", HTML_TOKEN_TAGS),
        PSAT("center", HTML_TOKEN_TAGS),
        PSAT("cite", HTML_TOKEN_TAGS),
        PSAT("code", HTML_TOKEN_TAGS),
        PSAT("col", HTML_TOKEN_TAGS),
        PSAT("colgroup", HTML_TOKEN_TAGS),
        PSAT("comment", HTML_TOKEN_TAGS),
        PSAT("dd", HTML_TOKEN_TAGS),
        PSAT("del", HTML_TOKEN_TAGS),
        PSAT("dfn", HTML_TOKEN_TAGS),
        PSAT("dir", HTML_TOKEN_TAGS),
        PSAT("div", HTML_TOKEN_TAGS),
        PSAT("dl", HTML_TOKEN_TAGS),
        PSAT("dt", HTML_TOKEN_TAGS),
        PSAT("em", HTML_TOKEN_TAGS),
        PSAT("embed", HTML_TOKEN_TAGS),
        PSAT("fieldset", HTML_TOKEN_TAGS),
        PSAT("font", HTML_TOKEN_TAGS),
        PSAT("form", HTML_TOKEN_TAGS),
        PSAT("frame", HTML_TOKEN_TAGS),
        PSAT("frameset", HTML_TOKEN_TAGS),
        PSAT("h1", HTML_TOKEN_TAGS),
        PSAT("h2", HTML_TOKEN_TAGS),
        PSAT("h3", HTML_TOKEN_TAGS),
        PSAT("h4", HTML_TOKEN_TAGS),
        PSAT("h5", HTML_TOKEN_TAGS),
        PSAT("h6", HTML_TOKEN_TAGS),
        PSAT("head", HTML_TOKEN_TAGS),
        PSAT("hr", HTML_TOKEN_TAGS),
        PSAT("html", HTML_TOKEN_TAGS),
        PSAT("i", HTML_TOKEN_TAGS),
        PSAT("iframe", HTML_TOKEN_TAGS),
        PSAT("img", HTML_TOKEN_TAGS),
        PSAT("input", HTML_TOKEN_TAGS),
        PSAT("ins", HTML_TOKEN_TAGS),
        PSAT("isindex", HTML_TOKEN_TAGS),
        PSAT("kbd", HTML_TOKEN_TAGS),
        PSAT("label", HTML_TOKEN_TAGS),
        PSAT("layer", HTML_TOKEN_TAGS),
        PSAT("legend", HTML_TOKEN_TAGS),
        PSAT("li", HTML_TOKEN_TAGS),
        PSAT("link", HTML_TOKEN_TAGS),
        PSAT("map", HTML_TOKEN_TAGS),
        PSAT("marquee", HTML_TOKEN_TAGS),
        PSAT("menu", HTML_TOKEN_TAGS),
        PSAT("meta", HTML_TOKEN_TAGS),
        PSAT("nextid", HTML_TOKEN_TAGS),
        PSAT("nobr", HTML_TOKEN_TAGS),
        PSAT("noembed", HTML_TOKEN_TAGS),
        PSAT("noframes", HTML_TOKEN_TAGS),
        PSAT("noscript", HTML_TOKEN_TAGS),
        PSAT("object", HTML_TOKEN_TAGS),
        PSAT("ol", HTML_TOKEN_TAGS),
        PSAT("option", HTML_TOKEN_TAGS),
        PSAT("p", HTML_TOKEN_TAGS),
        PSAT("param", HTML_TOKEN_TAGS),
        PSAT("pre", HTML_TOKEN_TAGS),
        PSAT("q", HTML_TOKEN_TAGS),
        PSAT("s", HTML_TOKEN_TAGS),
        PSAT("samp", HTML_TOKEN_TAGS),
        PSAT("pre", HTML_TOKEN_TAGS),
        PSAT("q", HTML_TOKEN_TAGS),
        PSAT("s", HTML_TOKEN_TAGS),
        PSAT("samp", HTML_TOKEN_TAGS),
        PSAT("script", HTML_TOKEN_TAGS),
        PSAT("select", HTML_TOKEN_TAGS),
        PSAT("small", HTML_TOKEN_TAGS),
        PSAT("span", HTML_TOKEN_TAGS),
        PSAT("strike", HTML_TOKEN_TAGS),
        PSAT("strong", HTML_TOKEN_TAGS),
        PSAT("style", HTML_TOKEN_TAGS),
        PSAT("sub", HTML_TOKEN_TAGS),
        PSAT("sup", HTML_TOKEN_TAGS),
        PSAT("table", HTML_TOKEN_TAGS),
        PSAT("tbody", HTML_TOKEN_TAGS),
        PSAT("td", HTML_TOKEN_TAGS),
        PSAT("textarea", HTML_TOKEN_TAGS),
        PSAT("tfoot", HTML_TOKEN_TAGS),
        PSAT("th", HTML_TOKEN_TAGS),
        PSAT("thead", HTML_TOKEN_TAGS),
        PSAT("title", HTML_TOKEN_TAGS),
        PSAT("tr", HTML_TOKEN_TAGS),
        PSAT("tt", HTML_TOKEN_TAGS),
        PSAT("u", HTML_TOKEN_TAGS),
        PSAT("ul", HTML_TOKEN_TAGS),
        PSAT("var", HTML_TOKEN_TAGS),
        PSAT("wbr", HTML_TOKEN_TAGS),
        PSAT("xmp", HTML_TOKEN_TAGS),
        
        //PSAT("name", HTML_TOKEN_ARGUMENTS),
        //PSAT("property", HTML_TOKEN_ARGUMENTS),
        //PSAT("href", HTML_TOKEN_ARGUMENTS),
        //PSAT("class", HTML_TOKEN_ARGUMENTS),
        //PSAT("type", HTML_TOKEN_ARGUMENTS),
        //PSAT("content", HTML_TOKEN_ARGUMENTS),
        //PSAT("src", HTML_TOKEN_ARGUMENTS),
        //PSAT("width", HTML_TOKEN_ARGUMENTS),
        //PSAT("height", HTML_TOKEN_ARGUMENTS),
        //PSAT("charset", HTML_TOKEN_ARGUMENTS),
        //PSAT("lang", HTML_TOKEN_ARGUMENTS)
    
    };

    parse_context_language_html = create_parse_context(app, kw, ArrayCount(kw), 0, 0);
}
#undef PSAT

#endif

// BOTTOM

