# Project Name
TARGET := my_project

# Directories
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
LIB_DIR := lib
TEST_DIR := tests

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -I$(INC_DIR) -I$(LIB_DIR)
LDFLAGS := 

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Default target
all: $(BUILD_DIR)/$(TARGET)

# Build target
$(BUILD_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✅ Build complete: $@"

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	@echo "🧹 Cleaned build files."

# Run (optional target)
.PHONY: run
run: all
	./$(BUILD_DIR)/$(TARGET)

# Unit Tests (optional)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.test.o, $(TEST_SRCS))
TEST_BIN := $(BUILD_DIR)/run_tests

.PHONY: test
test: $(TEST_BIN)
	@echo "🚀 Running tests..."
	@./$(TEST_BIN)

$(TEST_BIN): $(OBJS) $(TEST_OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "✅ Built tests: $@"

$(BUILD_DIR)/%.test.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all check-deps

all: check-deps $(BUILD_DIR)/$(TARGET)

check-deps:
	@./scripts/check_deps.sh