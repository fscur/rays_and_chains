#todo: pass debug/release as parameter
clear 

cd engine
./build_engine_debug.sh
cd ..

cd libs
./build_gfx_opengl.sh
./build_window_glfw.sh
./build_ui_renderer_imgui.sh
./build_libs_debug.sh r_logger_outputstring_device
cd ..

cd apps
./build_apps_debug.sh sandbox
./build_apps_debug.sh hammer
cd ..
