clear

inc_dir="-Isrc -Iinc"
lib_dir=lib
bin_dir=bin/linux/libs
src_dir=src
compiler_flags="-std=c11 -ggdb -Wl,-rpath=$lib_dir -Wl,-rpath=$bin_dir -Wall -Wformat -D_DEBUG=1 -D_GNU_SOURCE -Wno-unused-function" 

mkdir bin -p
cd bin
mkdir linux -p
cd linux
mkdir libs -p
cd ../..

gcc $compiler_flags -o $bin_dir/$1.so $src_dir/libs/$1/$1.linux.c -shared -fPIC \
$inc_dir \
-L$lib_dir -L$bin_dir
# \
#-l:lib_window.so -l:lib_server.so
