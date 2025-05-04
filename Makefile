# Project name
TARGET := my_project

# Directories
SRC_DIR := src
INC_DIRS := include lib/minunit
BUILD_DIR := build
TEST_DIR := tests

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra $(foreach dir,$(INC_DIRS),-I$(dir))
LDFLAGS := 

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
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
