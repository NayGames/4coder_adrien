#include "4coder_default_include.cpp"

// NOTE(Adrien) Language not complety implemented
#include "languages/4coder_language_html.h"
#include "languages/4coder_language_css.h"
#include "languages/4coder_language_lua.h"

OPEN_FILE_HOOK_SIG(adrien_file_settings){
    // NOTE(allen|a4.0.8): The get_parameter_buffer was eliminated
    // and instead the buffer is passed as an explicit parameter through
    // the function call.  That is where buffer_id comes from here.
    Buffer_Summary buffer = get_buffer(app, buffer_id, AccessAll);
    Assert(buffer.exists);
	
	bool32 forced_virtual_whitespace = false;
    bool32 treat_as_code = false;
    bool32 treat_as_todo = false;
	bool32 lex_without_strings = false;
    
    CString_Array extensions = get_code_extensions(&global_config.code_exts);
    
    Parse_Context_ID parse_context_id = 0;
	
    if (buffer.file_name != 0 && buffer.size < (16 << 20)){
        String name = make_string(buffer.file_name, buffer.file_name_len);
        String ext = file_extension(name);
        for (int32_t i = 0; i < extensions.count; ++i){
            if (match(ext, extensions.strings[i])){
                treat_as_code = true;
				
				print_message(app, ext.str, ext.size);
				
                if (match(ext, "cs")){
                    if (parse_context_language_cs == 0){
                        init_language_cs(app);
                    }
                    parse_context_id = parse_context_language_cs;
                }
                
                if (match(ext, "java")){
                    if (parse_context_language_java == 0){
                        init_language_java(app);
                    }
                    parse_context_id = parse_context_language_java;
                }
                
                if (match(ext, "rs")){
                    if (parse_context_language_rust == 0){
                        init_language_rust(app);
                    }
                    parse_context_id = parse_context_language_rust;
                    lex_without_strings = true;
                }
                
                if (match(ext, "cpp") || match(ext, "h") || match(ext, "c") || match(ext, "hpp") || match(ext, "cc")){
                    if (parse_context_language_cpp == 0){
                        init_language_cpp(app);
                    }
                    parse_context_id = parse_context_language_cpp;
                }
                
                // TODO(NAME): Real GLSL highlighting
                if (match(ext, "glsl")){
                    if (parse_context_language_cpp == 0){
                        init_language_cpp(app);
                    }
                    parse_context_id = parse_context_language_cpp;
                }
                
                // TODO(NAME): Real Objective-C highlighting
                if (match(ext, "m")){
                    if (parse_context_language_cpp == 0){
                        init_language_cpp(app);
                    }
                    parse_context_id = parse_context_language_cpp;
                }
				
                if (match(ext, "html")){
                    if (parse_context_language_html == 0){
                        init_language_html(app);
						forced_virtual_whitespace = true;
                    }
                    parse_context_id = parse_context_language_html;
                }
                
				if (match(ext, "css")){
					if (parse_context_language_css == 0){
						init_language_css(app);
						forced_virtual_whitespace = true;
					} 
					parse_context_id = parse_context_language_css;
				}
				
				if (match(ext, "lua")){
					if (parse_context_language_lua == 0){
						init_language_lua(app);
						forced_virtual_whitespace = true;
					}
					parse_context_id = parse_context_language_lua;
				}
				
                break;
            }
        }
        
        if (!treat_as_code){
            treat_as_todo = match_insensitive(front_of_directory(name), "todo.txt");
        }
    }
    
    int32_t map_id = (treat_as_code && !forced_virtual_whitespace)?((int32_t)default_code_map):((int32_t)mapid_file);
    int32_t map_id_query = 0;
    
    buffer_set_setting(app, &buffer, BufferSetting_MapID, default_lister_ui_map);
    buffer_get_setting(app, &buffer, BufferSetting_MapID, &map_id_query);
    Assert(map_id_query == default_lister_ui_map);
    
    buffer_set_setting(app, &buffer, BufferSetting_WrapPosition, global_config.default_wrap_width);
    buffer_set_setting(app, &buffer, BufferSetting_MinimumBaseWrapPosition, global_config.default_min_base_width);
    buffer_set_setting(app, &buffer, BufferSetting_MapID, map_id);
    buffer_get_setting(app, &buffer, BufferSetting_MapID, &map_id_query);
    Assert(map_id_query == map_id);
    buffer_set_setting(app, &buffer, BufferSetting_ParserContext, parse_context_id);
    
    // NOTE(allen): Decide buffer settings
    bool32 wrap_lines = true;
    bool32 use_virtual_whitespace = false;
    bool32 use_lexer = false;
    if (treat_as_todo){
        lex_without_strings = true;
        wrap_lines = true;
        use_virtual_whitespace = true;
        use_lexer = true;
    }
    else if (treat_as_code){
        wrap_lines = global_config.enable_code_wrapping;
        use_virtual_whitespace = global_config.enable_virtual_whitespace;
        use_lexer = true;
    }
    if (match(make_string(buffer.buffer_name, buffer.buffer_name_len), "*compilation*")){
        wrap_lines = false;
    }
    //if (buffer.size >= (192 << 10)){
    if (buffer.size >= (128 << 10)){
        wrap_lines = false;
        use_virtual_whitespace = false;
    }
	
	if (forced_virtual_whitespace){
		use_virtual_whitespace = false;
	}
	
    // NOTE(allen|a4.0.12): There is a little bit of grossness going on here.
    // If we set BufferSetting_Lex to true, it will launch a lexing job.
    // If a lexing job is active when we set BufferSetting_VirtualWhitespace, the call can fail.
    // Unfortunantely without tokens virtual whitespace doesn't really make sense.
    // So for now I have it automatically turning on lexing when virtual whitespace is turned on.
    // Cleaning some of that up is a goal for future versions.
    buffer_set_setting(app, &buffer, BufferSetting_LexWithoutStrings, lex_without_strings);
    buffer_set_setting(app, &buffer, BufferSetting_WrapLine, wrap_lines);
    buffer_set_setting(app, &buffer, BufferSetting_VirtualWhitespace, use_virtual_whitespace);
    buffer_set_setting(app, &buffer, BufferSetting_Lex, use_lexer);
     
    // no meaning for return
    return(0);
}
			
OPEN_FILE_HOOK_SIG(adrien_new_file){
	Buffer_Summary buffer = get_buffer(app, buffer_id, AccessAll);
	char str[] = "/*\nNew File\n*/\n\n\n";
	buffer_replace_range(app, &buffer, 0, 0, str, sizeof(str)-1);

	return(0);
}

bool
CubicUpdateFixedDuration1(float *P0, float *V0, float P1, float V1, float Duration, float dt)
{
	bool Result = false;
    
     if(dt > 0)
    {
        if(Duration < dt)
        {
            *P0 = P1 + (dt - Duration)*V1;
            *V0 = V1;
            Result = true;
        }
        else
        {
            float t = (dt / Duration);
            float u = (1.0f - t);
            
            float C0 = 1*u*u*u;
            float C1 = 3*u*u*t;
            float C2 = 3*u*t*t;
            float C3 = 1*t*t*t;
            
            float dC0 = -3*u*u;
            float dC1 = -6*u*t + 3*u*u;
            float dC2 =  6*u*t - 3*t*t;
            float dC3 =  3*t*t;
            
            float B0 = *P0;
            float B1 = *P0 + (Duration / 3.0f) * *V0;
            float B2 = P1 - (Duration / 3.0f) * V1;
            float B3 = P1;
            
            *P0 = C0*B0 + C1*B1 + C2*B2 + C3*B3;
            *V0 = (dC0*B0 + dC1*B1 + dC2*B2 + dC3*B3) * (1.0f / Duration);
        }
    }
    
    return(Result);
}


struct Casey_Scroll_Velocity
{
    float x, y, t;
};

Casey_Scroll_Velocity casey_scroll_velocity_[16] = {};
Casey_Scroll_Velocity *casey_scroll_velocity = casey_scroll_velocity_ - 1;

SCROLL_RULE_SIG(casey_smooth_scroll_rule){
    Casey_Scroll_Velocity *velocity = casey_scroll_velocity + view_id;
    int result = 0;
    if(is_new_target)
    {
        if((*scroll_x != target_x) ||
           (*scroll_y != target_y))
        {
            velocity->t = 0.1f;
        }
    }
    
    if(velocity->t > 0)
    {
        result = !(CubicUpdateFixedDuration1(scroll_x, &velocity->x, target_x, 0.0f, velocity->t, dt) ||
                   CubicUpdateFixedDuration1(scroll_y, &velocity->y, target_y, 0.0f, velocity->t, dt));
    }
    
    velocity->t -= dt;
    if(velocity->t < 0)
    {
        velocity->t = 0;
        *scroll_x = target_x;
        *scroll_y = target_y;
    }
    
    return(result);
}

static void
UpdateThemeColor(Application_Links *app)
{
    int unsigned Constant   = 0xFF6B8E23;
    int unsigned Background = 0xFF1E1E1E;
	int unsigned Back_Cycle = 0x0CA00000;
	
	int unsigned Red   = 0xFFB04732;
	int unsigned Blue  = 0xFF5AB7BE;
	int unsigned Green = 0xFF75993C;
	
    Theme_Color common_colors[] =
    {
		{Stag_Comment, 0xFF8A8071},
        {Stag_Keyword, Red},
        {Stag_Preproc, Blue},
        {Stag_Include, Constant},
        {Stag_Back, Background},
        {Stag_Margin, Background},
        {Stag_Margin_Hover, Background},
        {Stag_Margin_Active, Background},
        {Stag_List_Item,Background},
        {Stag_List_Item_Hover, 0xFF934420},
        {Stag_List_Item_Active, 0xFF934420},
        {Stag_Default, 0xFFA98247},
		{Stag_Bar, 0xFFADA49A},
        {Stag_Pop1, Red},
		{Stag_Pop2, Red},
		
		{Stag_Back_Cycle_1, Back_Cycle},
		{Stag_Back_Cycle_2, Back_Cycle},
		{Stag_Back_Cycle_3, Back_Cycle},
		{Stag_Back_Cycle_4, Back_Cycle},
		
		{Stag_Text_Cycle_1, Red},
		{Stag_Text_Cycle_2, Red},
		{Stag_Text_Cycle_3, Red},
		{Stag_Text_Cycle_4, Red},
		
		{Stag_Highlight_Cursor_Line, 0xFF222222},
		
		{Stag_Str_Constant, Green},
        {Stag_Char_Constant, Green},
        {Stag_Int_Constant, Green},
        {Stag_Float_Constant, Green},
        {Stag_Bool_Constant, Green},
    };
    set_theme_colors(app, common_colors, ArrayCount(common_colors));
}

START_HOOK_SIG(adrien_start)
{
    default_4coder_initialize(app);
    default_4coder_initialize(app);
    
    exec_command(app, hide_scrollbar);
    exec_command(app, open_panel_vsplit);
    exec_command(app, hide_scrollbar);
    exec_command(app, change_active_panel);
    
    change_theme(app, literal("Handmade Hero"));
    set_global_face_by_name(app, literal("Droid Sans Mono"), true);
    UpdateThemeColor(app);
    
    return(0);
}

CUSTOM_COMMAND_SIG(write_parentheses)
CUSTOM_DOC("Inserts parentheses.")
{
	write_string(app, make_lit_string("()"));
}

CUSTOM_COMMAND_SIG(write_braces)
CUSTOM_DOC("Inserts braces.")
{
	write_string(app, make_lit_string("{\n\n}"));
}

CUSTOM_COMMAND_SIG(write_brackets)
CUSTOM_DOC("Inserts brackets.")
{
	write_string(app, make_lit_string("[]"));
}

CUSTOM_COMMAND_SIG(write_double_quotes)
CUSTOM_DOC("Inserts double quotes.")
{
	write_string(app, make_lit_string("\"\""));
}

CUSTOM_COMMAND_SIG(write_single_quotes)
CUSTOM_DOC("Inserts single quotes.")
{
	write_string(app, make_lit_string("''"));
}

extern "C" GET_BINDING_DATA(get_bindings)
{
	Bind_Helper context_actual = begin_bind_helper(data, size);
	Bind_Helper* context = &context_actual;
    
    set_start_hook(context, adrien_start);
    set_command_caller(context, default_command_caller);
    set_render_caller(context, default_render_caller);
    set_open_file_hook(context, adrien_file_settings);
    set_new_file_hook(context, adrien_new_file);
	set_scroll_rule(context, casey_smooth_scroll_rule);
    set_end_file_hook(context, end_file_close_jump_list);
    
	default_keys(context);
	
    begin_map(context, mapid_global);
	
	bind(context, 'm', MDFR_ALT, set_mark);
	
	bind(context, '=', MDFR_CTRL, write_zero_struct);
	
	bind(context, key_right, MDFR_ALT, change_active_panel); 
	bind(context, key_left, MDFR_ALT, change_active_panel);
	bind(context, key_f11, MDFR_NONE, toggle_fullscreen);
	bind(context, key_f4, MDFR_ALT, exit_4coder);
	
	end_map(context);

	begin_map(context, mapid_file);
	
	bind(context, '(', MDFR_NONE, write_parentheses);
	bind(context, '{', MDFR_NONE, write_braces);
	bind(context, '[', MDFR_NONE, write_brackets);
	bind(context, '\'', MDFR_NONE, write_single_quotes);
	bind(context, '"', MDFR_NONE, write_double_quotes);
	
	end_map(context);

	end_bind_helper(context);
	
	return(context->write_total);
}