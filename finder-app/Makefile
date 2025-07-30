# Makefile for writer application
# Supports both native compilation and cross-compilation for aarch64

# Variables
TARGET = writer
SOURCES = writer.c
OBJECTS = $(SOURCES:.c=.o)

# Cross-compilation support
# If CROSS_COMPILE is not specified, use native compiler
# If CROSS_COMPILE is specified (e.g., aarch64-none-linux-gnu-), use cross compiler
CC = $(CROSS_COMPILE)gcc

# Compiler flags
CFLAGS = -Wall -Werror -g -O2

# Default target - builds the writer application
all: $(TARGET)

# Build the writer application
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target - removes writer application and all .o files
clean:
	rm -f $(TARGET) $(OBJECTS)

# Install target (optional)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Phony targets
.PHONY: all clean install

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build the writer application (default)"
	@echo "  clean   - Remove writer application and all .o files"
	@echo "  install - Install writer to /usr/local/bin/"
	@echo "  help    - Show this help message"
	@echo ""
	@echo "Cross-compilation:"
	@echo "  make                                    # Native compilation"
	@echo "  make CROSS_COMPILE=aarch64-none-linux-gnu-  # Cross-compile for aarch64"