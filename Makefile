# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall

SRC_DIR = src
LIB_DIR = lib

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
LIB_FILES = $(wildcard $(LIB_DIR)/**/*.c)

OBJ_FILES = $(LIB_FILES:.c=.o)

INCLUDES = $(addprefix -I, $(dir $(wildcard lib/*/)))

all: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

test:
	echo $(DIRECTORY)

main: $(LIB_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) -o tubes $(filter-out %_driver.c,$(LIB_FILES)) $(SRC_DIR)/main.c

clean:
	rm -f $(OBJ_FILES) $(TARGET)

.PHONY: all clean
