APP_PATH = build/KNN-classifier
CC = g++
DEBUG = true
C_FLAGS = -w
SRC_DIR = src
BUILD_DIR = build/dep

CPP_SRC = $(shell find $(SRC_DIR) -name '*.cpp')
CPP_OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_SRC))

ifeq ($(DEBUG), true)
C_FLAGS += -g0
else
C_FLAGS += -g3
endif

all: $(APP_PATH)

$(APP_PATH): $(CPP_OBJ) | $(BUILD_DIR)
	$(CC) $(C_FLAGS) $(CPP_OBJ) -o $(APP_PATH)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	rm -rf build

run: $(APP_PATH)
	./$(APP_PATH)
