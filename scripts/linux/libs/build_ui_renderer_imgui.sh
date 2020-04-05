pushd () {
    command pushd "$@" > /dev/null
}

popd () {
    command popd "$@" > /dev/null
}

root="../../.."
inc_dir=$root/inc
lib_dir=$root/lib/linux
bin_dir=$root/bin/linux/libs
src_dir=$root/src

compiler_flags="-std=c11 -ggdb -Wl,-rpath=$lib_dir -Wl,-rpath=$bin_dir -Wall -Wformat -D_DEBUG=1 -D_GNU_SOURCE -DCIMGUI_DEFINE_ENUMS_AND_STRUCTS -Wno-unused-function" 

pushd $root
mkdir bin -p
cd bin
mkdir linux -p
cd linux
mkdir libs -p
cd ../..
popd

echo Compiling r_ui_renderer_imgui.

gcc $compiler_flags -o $bin_dir/r_ui_renderer_imgui.so $src_dir/libs/r_ui_renderer_imgui/r_ui_renderer_imgui.linux.c -shared -fPIC \
-I$inc_dir -I$src_dir \
-L$lib_dir -L$bin_dir \
-l:cimgui.so -lGL \
`pkg-config --cflags glfw3` `pkg-config --static --libs glfw3`

echo Done.