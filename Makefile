# Variables
TARGET = bin/dbview
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Iinclude

# Default target
default: $(TARGET)

# Clean target
clean:
	rm -f obj/*.o
	rm -f bin/*

# Build target
$(TARGET): $(OBJ)
	$(CC) -o $@ $^

# Compile object files
obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Run target
run: $(TARGET)
	./$(TARGET)
