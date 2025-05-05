# Project name
TARGET := my_app

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
TEST_DIR := tests

INC_DIRS := \
include \
lib/minunit \

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -std=gnu11 $(foreach dir,$(INC_DIRS),-I$(dir))
LDFLAGS := 

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

TARGET_BINARY := $(BIN_DIR)/$(TARGET)

# Default target
.PHONY: all check-deps
all: $(TARGET_BINARY) 

$(TARGET_BINARY): CFLAGS += -DCOMPILE_MAIN

# Build the target
$(TARGET_BINARY): $(OBJS)
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
	rm -rf $(BUILD_DIR)/* $(TARGET_BINARY)
	@echo "🧹 Cleaned build files."

# Run target
.PHONY: run
run: all
	@echo "🚀 Running app..."
	./$(TARGET_BINARY)

# Dependency check

# Unit test target
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.test.o, $(TEST_SRCS))
TEST_BINS := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/$(TEST_DIR)/%,$(TEST_SRCS))

.PHONY: test

test: $(TEST_BINS)
	@echo "🔬 Running tests..."
	@for bin in $^; do \
		echo "👉 Running $$bin"; \
		$$bin || echo "❌ Test $$bin failed."; \
	done

$(BUILD_DIR)/$(TEST_DIR)/%: $(TEST_DIR)/%.c $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $< $(OBJS)
