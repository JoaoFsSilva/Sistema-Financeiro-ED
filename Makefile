CXX      = g++
CXXFLAGS = -std=c++17 -Wall -I./libs/raylib/include -I./src
LDFLAGS  = -L./libs/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm

SRC_DIR   = src
BUILD_DIR = build

SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = $(BUILD_DIR)/financas

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.exe $(BUILD_DIR)/financas $(BUILD_DIR)/**/*.o

.PHONY: all clean
