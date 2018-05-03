clear
mkdir bin -p
cd bin
rm -f main
gcc -std=c99 -ggdb -o main ../src/main.c \
-I../inc/ -I../inc/gl3w \
-L../lib \
-l:cimgui.so -lGL \
-Wl,-rpath=../lib \
-Wall -Wformat \
`pkg-config --cflags glfw3` `pkg-config --static --libs glfw3`
./main