SRC_DIR = ./src
OBJ_DIR = ./build
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES))
all:
	gcc -Wall -pedantic $(SRC_DIR)/reader.c -o $(OBJ_DIR)/reader
	gcc -Wall -pedantic $(SRC_DIR)/writer.c -o $(OBJ_DIR)/writer

