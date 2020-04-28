SHELL = bash
CC = gcc

SRC_DIR = src
TST_DIR = test
OBJ_DIR = obj
BIN_DIR = bin

CFLAGS = -Wall -g
CHECK_LIBS = -lcheck -lm -lpthread -lrt -lsubunit

run_check_linkedlist: check_linkedlist
	$(BIN_DIR)/$<

check_linkedlist: linkedlist.o check_linkedlist.o $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(OBJ_DIR)/linkedlist.o $(OBJ_DIR)/check_linkedlist.o $(CHECK_LIBS)

check_linkedlist.o: $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/$@ -c $(TST_DIR)/check_linkedlist.c 

linkedlist.o: $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/$@ -c $(SRC_DIR)/linkedlist.c

$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf bin obj