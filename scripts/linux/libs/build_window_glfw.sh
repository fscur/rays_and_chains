clear

inc_dir="-Isrc -Iinc"
lib_dir=lib/linux
bin_dir=bin/linux/libs
src_dir=src
compiler_flags="-std=c11 -ggdb -Wl,-rpath=$lib_dir -Wl,-rpath=$bin_dir -Wall -Wformat -D_DEBUG=1 -D_GNU_SOURCE -Wno-unused-function" 

mkdir bin -p
cd bin
mkdir linux -p
cd linux
mkdir libs -p
cd ../..

gcc $compiler_flags -o $bin_dir/r_window_glfw.so $src_dir/libs/r_window_glfw/r_window_glfw.linux.c -shared -fPIC \
$inc_dir \
-L$lib_dir -L$bin_dir \
-lGL \
`pkg-config --cflags glfw3` `pkg-config --static --libs glfw3`
