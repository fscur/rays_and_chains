clear
inc_dir=../inc
lib_dir=../lib
bin_dir=../bin
src_dir=../src
compiler_flags="-std=c99 -ggdb -Wl,-rpath=$lib_dir -Wl,-rpath=$bin_dir -Wall -Wformat -D_DEBUG=1"
mkdir bin -p
cd bin

# gcc $compiler_flags -o $bin_dir/libr_window.so $src_dir/app/r_window.c -shared -fPIC \
# -I$inc_dir -I$inc_dir/gl3w \
# -L$lib_dir -L$bin_dir \
# -l:cimgui.so -lGL \
# `pkg-config --cflags glfw3` `pkg-config --static --libs glfw3`

gcc $compiler_flags -o $bin_dir/libr_app.so $src_dir/app/r_app.c -shared -fPIC \
-I$inc_dir -I$inc_dir/gl3w \
-L$lib_dir -L$bin_dir \
-l:cimgui.so -lGL \
`pkg-config --cflags glfw3` `pkg-config --static --libs glfw3`
# gcc $compiler_flags -o $bin_dir/libr_app.so $src_dir/app/r_app.c -shared -fPIC \
# -I$inc_dir -I$inc_dir/gl3w \
# -L$lib_dir -L$bin_dir \
# -l:cimgui.so -lGL \
# `pkg-config --cflags glfw3` `pkg-config --static --libs glfw3`

rm -f rays_and_chains
gcc $compiler_flags -o rays_and_chains $src_dir/linux/main.c -lm -ldl \
-I$inc_dir -I$inc_dir/gl3w \
-L$lib_dir -L$bin_dir \
-l:cimgui.so -l:libr_window.so -lGL \
`pkg-config --cflags glfw3` `pkg-config --static --libs glfw3`
#./rays_and_chains

#-l:cimgui.so -l:libr_app.so -lGL \