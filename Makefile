# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall 

# Directories
SRC_DIR = src
LIB_DIR = lib

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
LIB_FILES = $(wildcard $(LIB_DIR)/**/*.c)

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o) $(LIB_FILES:.c=.o)

# Header files
INCLUDES = -I$(LIB_DIR)

# Output binary
TARGET = tubes

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(TARGET)

.PHONY: all clean
