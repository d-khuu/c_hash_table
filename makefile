CFLAGS = -std=c11 -pedantic -Wall -g
CC = gcc
SRC_DIR = src
BUILD_DIR = build
PROG = hash_table.x86_64
SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
HEADERS = $(shell find $(SRC_DIR) -name '*.h')


all: $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -f $(BUILD_DIR)/*.o $(SRC_DIR)/*.h.gch $(OBJS) $(PROG)

archive:
	zip $(USER) $(SRC) $(HEADERS) *.txt Makefile
