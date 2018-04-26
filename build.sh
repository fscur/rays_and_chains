clear
mkdir bin -p
cd bin
rm -f *.*
rm -f main

#gcc -o foo foo.c -L$(prefix)/lib -lfoo -Wl,-rpath=$(prefix)/lib

gcc -o main ../src/main.c -L../lib -l:cimgui.so -Wl,-rpath=../lib -I../inc/ -I../inc/gl3w `pkg-config --cflags glfw3` -Wall -Wformat -lGL `pkg-config --static --libs glfw3`
./main