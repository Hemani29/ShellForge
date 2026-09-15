CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
SRC = src/main.c src/input.c src/process.c src/pipe.c src/ls_grep_pipe.c
TARGET = bin/shellforge

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -rf bin/*
