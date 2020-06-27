@echo off

call copy 4coder_adrien.cpp ..\

pushd languages
call copy 4coder_language_css.h ..\..\languages
call copy 4coder_language_html.h ..\..\languages
call copy 4coder_language_lua.h ..\..\languages
popd

call copy config.4coder ..\

call copy build.bat ..\
