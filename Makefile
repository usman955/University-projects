all: compile link
#add all the header implementation .cpp file names here after main.cpp
compile:
g++ -Isrc/include -c main.cpp Implementation/header.cpp 	

g++ -o Executable/main.exe main.o header.o -Lsrc/lib -lsfml-main -lsfml-graphics -lsfml-window -lsfml-system
del *.o
Executable\main.exe