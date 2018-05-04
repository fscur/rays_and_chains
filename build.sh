clear
inc_dir=../inc
lib_dir=../lib
src_dir=../src
mkdir bin -p
cd bin
rm -f rays_and_chains
gcc -std=c99 -ggdb -o rays_and_chains $src_dir/linux/main.c \
-I$inc_dir -I$inc_dir/gl3w \
-L$lib_dir \
-l:cimgui.so -lGL \
-Wl,-rpath=$lib_dir \
-Wall -Wformat \
`pkg-config --cflags glfw3` `pkg-config --static --libs glfw3`
./rays_and_chains