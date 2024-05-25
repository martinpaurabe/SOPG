SRC_DIR = ./source
OBJ_DIR = ./build
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)%.c,
$(OBJ_DIR)%.o,$(SRC_FILES))
all: $(OBJ_FILES)
gcc -o $(OBJ_DIR)/a.out $(OBJ_FILES)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
gcc -c $< -o $@
