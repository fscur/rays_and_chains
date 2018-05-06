clear
inc_dir=../inc
lib_dir=../lib
src_dir=../src
compiler_flags="-std=c99 -ggdb -Wl,-rpath=$lib_dir -Wall -Wformat -D_DEBUG=1"
mkdir bin -p
cd bin

gcc $compiler_flags -o $lib_dir/libr_app.so $src_dir/app/r_app.c -shared -fPIC 

rm -f rays_and_chains
gcc $compiler_flags -o rays_and_chains $src_dir/linux/main.c \
-I$inc_dir -I$inc_dir/gl3w \
-L$lib_dir \
-l:cimgui.so -l:libr_app.so -lGL \
`pkg-config --cflags glfw3` `pkg-config --static --libs glfw3`
./rays_and_chains