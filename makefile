CC := g++
CFLAGS := -Wall -Wextra -Iinclude -std=c++17 -framework CoreFoundation -framework AudioToolbox -DAUREP_DEBUG
# -g

SRC_DIR := src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN := $(BUILD_DIR)/aurep

MAIN_SRC := $(SRC_DIR)/main.cpp
SRCS := $(filter-out $(MAIN_SRC), $(shell find $(SRC_DIR) -name '*.cpp'))
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
MAIN_OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(MAIN_SRC))

all: $(BIN)

$(BIN): $(OBJS) $(MAIN_OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(MAIN_OBJ): $(MAIN_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(BIN)

clean:
	rm -rf $(BUILD_DIR)

install:
	sudo cp ./$(BIN) /usr/local/bin

.PHONY: all clean
