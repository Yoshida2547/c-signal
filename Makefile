# Project name
TARGET := my_app

# Directories
SRC_DIR := src
BUILD_DIR := build
TEST_DIR := tests

INC_DIRS := \
include \
lib/minunit \


# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -std=c11 $(foreach dir,$(INC_DIRS),-I$(dir))
LDFLAGS := 

# Source and object files
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Default target
.PHONY: all check-deps
all: check-deps $(BUILD_DIR)/$(TARGET)

# Build the target
$(BUILD_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✅ Build complete: $@"

# Compile each source file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	@echo "🧹 Cleaned build files."

# Run target
.PHONY: run
run: all
	./$(BUILD_DIR)/$(TARGET)

# Dependency check
.PHONY: check-deps
check-deps:
	@./scripts/check_deps.sh

# Unit test target
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

$(BUILD_DIR)/%.test.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

