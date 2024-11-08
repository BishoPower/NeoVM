# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wextra -std=c11 -Iutils

# Source files
SRCS = neovm.c utils/utils.c

# Header files
HDRS = neovm.h utils/utils.h

# Output executable
TARGET = neovm

# Object files
OBJS = neovm.o utils/utils.o

# Build target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

neovm.o: neovm.c neovm.h
	$(CC) $(CFLAGS) -c neovm.c

utils/utils.o: utils/utils.c
	$(CC) $(CFLAGS) -c utils/utils.c -o utils/utils.o

# Clean target
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean