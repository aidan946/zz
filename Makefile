# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++26 -Wall -Wextra -Wpedantic -O2
DEBUGFLAGS = -g -O0 -DDEBUG
TARGET = zz
SOURCES = $(wildcard src/*.cpp)
BUILDDIR = build
OBJECTS = $(SOURCES:src/%.cpp=$(BUILDDIR)/%.o)
TARGET_PATH = $(BUILDDIR)/$(TARGET)

# Default target
all: $(BUILDDIR) $(TARGET_PATH)

# Create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Build the executable
$(TARGET_PATH): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET_PATH) $(OBJECTS)

# Build object files
$(BUILDDIR)/%.o: src/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug build
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILDDIR)

# Install (optional)
install: $(TARGET_PATH)
	install -d $(DESTDIR)/usr/local/bin
	install -m 755 $(TARGET_PATH) $(DESTDIR)/usr/local/bin/

# Uninstall
uninstall:
	rm -f $(DESTDIR)/usr/local/bin/$(TARGET)

# Run the program
run: $(TARGET_PATH)
	./$(TARGET_PATH)

# Build and run with test arguments
test: $(TARGET_PATH)
	./$(TARGET_PATH) -r 2 --no-icons

.PHONY: all debug clean install uninstall run test
