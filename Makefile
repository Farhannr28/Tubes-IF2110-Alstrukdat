CC = gcc
CFLAGS = -Wall

SRC_DIR = src
LIB_DIR = lib

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
LIB_FILES = $(wildcard $(LIB_DIR)/**/*.c)
LIB_FILES_NON_DRIVER=$(filter-out %_driver.c,$(LIB_FILES)) 

INCLUDES = $(addprefix -I, $(dir $(wildcard lib/*/)))

all: $(LIB_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) -o tubes $(LIB_FILES_NON_DRIVER) $(SRC_DIR)/main.c

test: $(filter %_driver.c,$(LIB_FILES))
	@$(foreach driver, $^, \
		$(CC) $(CFLAGS) $(INCLUDES) -o $(patsubst %.c,%,$(notdir $(driver))) $(LIB_FILES_NON_DRIVER) $(driver); \
	)

.PHONY: all clean
