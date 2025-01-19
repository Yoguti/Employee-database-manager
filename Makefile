TARGET = bin/dbview
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

# Default target
default: $(TARGET)

# Run target
run: clean default
	./$(TARGET)

# Clean target
clean:
	rm -f obj/*.o
	rm -f bin/*
	rm -f *.db

# Build target
$(TARGET): $(OBJ)
	gcc -o $@ $^

# Compile object files
obj/%.o: src/%.c
	gcc -c $< -o $@ -Iinclude
