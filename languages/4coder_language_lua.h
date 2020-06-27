/*
4coder_language_lua.h - Sets up the C# language context.
*/

// TOP

#if !defined(FCODER_LANGUAGE_LUA_H)
#define FCODER_LANGUAGE_LUA_H

static Parse_Context_ID parse_context_language_lua;

#define PSAT(s, t) {s, sizeof(s)-1, t}
static void
init_language_lua(Application_Links *app){
    if (parse_context_language_lua != 0) return;
    
    Parser_String_And_Type kw[] = {
        PSAT("function", CPP_TOKEN_KEY_OTHER),
		PSAT("end", CPP_TOKEN_KEY_OTHER),
		PSAT("local", CPP_TOKEN_KEY_OTHER),
		PSAT("require", CPP_TOKEN_KEY_OTHER),
		PSAT("for", CPP_TOKEN_KEY_OTHER),
		PSAT("while", CPP_TOKEN_KEY_OTHER),
		PSAT("else", CPP_TOKEN_KEY_OTHER),
		PSAT("if", CPP_TOKEN_KEY_OTHER),
		PSAT("then", CPP_TOKEN_KEY_OTHER),
		PSAT("do", CPP_TOKEN_KEY_OTHER),
		PSAT("print", CPP_TOKEN_KEY_OTHER)
	};
    
    parse_context_language_lua = create_parse_context(app, kw, ArrayCount(kw), 0, 0);
}
#undef PSAT

#endif

// BOTTOM

