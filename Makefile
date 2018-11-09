#Makefile
all: main

main: file main.cpp
	g++ -std=c++11 File.o main.cpp -o main

file: File.cpp
	g++ -std=c++11 File.cpp -c -o File.o