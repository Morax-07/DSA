# Compilatore e flag
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Librerie e include
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
INCLUDE = -Iinclude

# Directory e file
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/AVLTree

# Regole per la build
all: $(TARGET)

$(TARGET): $(OBJS)
	#mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm $(TARGET)

# Regole ausiliarie
.PHONY: all clean