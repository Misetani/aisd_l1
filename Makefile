CC = g++
CPP_FLAGS = -std=c++20 -g -Wall -Wextra #-Werror

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))

HEADERS = $(wildcard *.h)

PROGRAM = program

all: run clean

run: $(PROGRAM)
	@./$(PROGRAM) || true

$(PROGRAM): $(OBJ)
	@$(CC) $(CPP_FLAGS) $(OBJ) -o $(PROGRAM)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CPP_FLAGS) -c $< -o $@

check: $(OBJ)
	@cppcheck $(SRC) $(HEADERS)

clean:
	@rm -rf $(OBJ_DIR) $(PROGRAM)