CXX = g++
CXXFLAGS = -Wall -Iinclude
LDFLAGS = -lncurses

SRC = src/main.cpp src/game.cpp src/snake.cpp src/apple.cpp
OBJ_DIR = obj
OBJ = $(SRC:src/%.cpp=$(OBJ_DIR)/%.o)

all: $(OBJ_DIR) snake

snake: $(OBJ)
	$(CXX) $(OBJ) $(CXXFLAGS) $(LDFLAGS) -o snake

$(OBJ_DIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) snake
