# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall

SRC_DIR = src
LIB_DIR = lib

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
LIB_FILES = $(wildcard $(LIB_DIR)/**/*.c)

INCLUDES = $(addprefix -I, $(dir $(wildcard lib/*/)))

test: $(filter %_driver.c,$(LIB_FILES))
	@$(foreach driver, $^, \
		$(CC) $(CFLAGS) $(INCLUDES) -o $(patsubst %.c,%,$(notdir $(driver))) $(filter-out %_driver.c,$(LIB_FILES)) $(driver); \
	)

all: $(LIB_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) -o tubes $(filter-out %_driver.c,$(LIB_FILES)) $(SRC_DIR)/main.c

.PHONY: all clean
