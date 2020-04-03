REM todo: fix build tools to follow the other folders pattern
REM todo: pass debug/release as parameter

call "engine\build_engine_debug.bat"
call "apps\build_apps_debug.bat" sandbox
call "libs\build_libs_debug.bat" r_window_glfw
call "libs\build_libs_debug.bat" r_ui_renderer_imgui
call "libs\build_libs_debug.bat" r_gfx_opengl
call "tools\build_bumpver_debug.bat"
call "tools\build_pdb_path_fixer_debug.bat"