# Variables
CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = cws
SRC = cws.c

# Default target
all: build

# Build target: compile the source code into the executable
build:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Run target: execute the program with sudo
run: build
	sudo ./$(TARGET)

# Clean up build files
clean:
	rm -f $(TARGET)
