pushd () {
    command pushd "$@" > /dev/null
}

popd () {
    command popd "$@" > /dev/null
}

root="../../../"
inc_dir=$root/inc
lib_dir=$root/lib
bin_dir=$root/bin/linux
src_dir=$root/src

compiler_flags="-std=c11 -ggdb -Wl,-rpath=$lib_dir -Wl,-rpath=$bin_dir -Wall -Wformat -D_DEBUG=1 -D_GNU_SOURCE -Wno-unused-function" 

pushd $root
mkdir bin -p
cd bin
mkdir linux -p
cd ..
popd

echo Compiling r_engine.

gcc $compiler_flags -o $bin_dir/r_engine $src_dir/engine/main/r_main.linux.c -lm -ldl -lrt \
-I$inc_dir -I$src_dir \
-L$lib_dir -L$bin_dir

echo Done.