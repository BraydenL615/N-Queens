#makefile for the n_Queens project.

CC = g++
CFLAGS = -g -Wall

main: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main

clean: 
	rm main

run:	main
	./main