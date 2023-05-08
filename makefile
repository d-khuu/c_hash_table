STANDARD = -std=c11
CFLAGS = -pedantic -Wall -g
OPT_FLAGS = -D OLD
CC = gcc
SRC_DIR = src
BUILD_DIR = build
PROG = hash_table.x86_64
SRC = $(shell find $(SRC_DIR) -name '*.c')
# Split OBJS into separate searches
OBJS = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
HEADERS = $(shell find $(SRC_DIR) -name '*.h')


all: $(OBJS)
	echo "Compiling Separate Chaining Hash Table"
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)
	./$(PROG)


old: $(OBJS)
	$(CC) $(CFLAGS) $(OPT_FLAGS) -c $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o
	echo "Compiling Open Addressing Hash Table"
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)
	./$(PROG)
	
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -f $(BUILD_DIR)/*.o $(SRC_DIR)/*.h.gch $(OBJS) $(PROG) vgcore.*

archive:
	zip $(USER) $(SRC) $(HEADERS) *.txt Makefile
