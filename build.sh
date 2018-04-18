clear
mkdir bin -p
cd bin
rm -f *.*
rm -f main
g++ -o main ../src/main.cpp -I../inc/ -I../inc/gl3w `pkg-config --cflags glfw3` -Wall -Wformat -lGL `pkg-config --static --libs glfw3`
./main

