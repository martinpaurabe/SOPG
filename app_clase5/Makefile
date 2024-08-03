SRC_DIR = ./src
OBJ_DIR = ./build
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_FILES))
all: $(OBJ_FILES)
	gcc -o $(OBJ_DIR)/client.out  $(SRC_DIR)/client.c
	gcc -o $(OBJ_DIR)/server.out  $(SRC_DIR)/server.c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc -c $< -o $@
