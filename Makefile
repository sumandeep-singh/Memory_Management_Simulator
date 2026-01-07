# Memory Allocator Simulator Makefile
# Author: Suman Kumar

# Compiler settings
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -pedantic
DEBUG_FLAGS := -g -DDEBUG

# Project configuration
PROJECT_NAME := memsim
SOURCE_FILE := main.cpp
EXECUTABLE := $(PROJECT_NAME)

# Default target
.PHONY: all clean debug install help

all: $(EXECUTABLE)

# Production build
$(EXECUTABLE): $(SOURCE_FILE)
	@echo "Building $(PROJECT_NAME)..."
	$(CXX) $(CXXFLAGS) $(SOURCE_FILE) -o $(EXECUTABLE)
	@echo "Build complete! Run with: ./$(EXECUTABLE)"

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(EXECUTABLE)
	@echo "Debug build complete!"

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -f $(EXECUTABLE) *.o
	@echo "Clean complete!"

# Install to /usr/local/bin (requires sudo)
install: $(EXECUTABLE)
	@echo "Installing $(PROJECT_NAME)..."
	sudo cp $(EXECUTABLE) /usr/local/bin/
	@echo "Installation complete!"

# Display help information
help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  debug   - Build with debug symbols"
	@echo "  clean   - Remove build artifacts"
	@echo "  install - Install to system (requires sudo)"
	@echo "  help    - Display this help message"
