APP_PATH = build/KNN-classifier
TEST_PATH = build/run_tests
CC = g++
DEBUG = true
C_FLAGS = -w
SRC_DIR = src
TEST_DIR  = tests
BUILD_DIR = build/dep

TEST_LIBS = -lgtest -lgtest_main -lpthread

CPP_SRC = $(shell find $(SRC_DIR) -name '*.cpp')
CPP_OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_SRC))

# Identify the object containing your app's main (adjust path if needed)
# This prevents "multiple definition of main" errors
APP_MAIN_OBJ = $(BUILD_DIR)/main.o
NON_MAIN_OBJ = $(filter-out $(APP_MAIN_OBJ), $(CPP_OBJ))

TEST_SRC = $(shell find $(TEST_DIR) -name '*.cpp')
TEST_OBJ = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/tests/%.o, $(TEST_SRC))

ifeq ($(DEBUG), true)
    C_FLAGS += -g3
else
    C_FLAGS += -g0
endif

all: $(APP_PATH)

$(APP_PATH): $(CPP_OBJ) | $(BUILD_DIR)
	$(CC) $(C_FLAGS) $(CPP_OBJ) -o $(APP_PATH)

$(TEST_PATH): $(TEST_OBJ) $(NON_MAIN_OBJ)
	$(CC) $(C_FLAGS) $(TEST_OBJ) $(NON_MAIN_OBJ) -o $(TEST_PATH) $(TEST_LIBS)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@

$(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	rm -rf build

run: $(APP_PATH)
	./$(APP_PATH)

test: $(TEST_PATH)
	./$(TEST_PATH)
