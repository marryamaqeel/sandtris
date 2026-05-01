# Compiler settings
CXX      := g++
# C++17 is required for std::optional used in SFML 3
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 

# SFML Linker flags
LDFLAGS  := -lsfml-graphics -lsfml-window -lsfml-system

# --- OS Detection & Specific Settings ---
ifeq ($(OS),Windows_NT)
    # Windows settings
    TARGET := Sandtris.exe
    RM     := rm -f
else
    # Unix-like systems (Linux, macOS)
    UNAME_S := $(shell uname -s)
    TARGET  := Sandtris
    RM      := rm -f

    ifeq ($(UNAME_S),Darwin)
        # macOS specific: Homebrew include/lib paths
        CXXFLAGS += -I/opt/homebrew/include -I/usr/local/include
        LDFLAGS  += -L/opt/homebrew/lib -L/usr/local/lib -Wl,-rpath,/opt/homebrew/lib -Wl,-rpath,/usr/local/lib
    else
        # Linux specific (Option 2): Explicitly point to the locally built SFML 3
        # This tells the compiler where the headers are
        CXXFLAGS += -I/usr/local/include
        # This tells the linker where the .so files are, AND tells the executable 
        # where to look for them when you actually run the game (-rpath)
        LDFLAGS  += -L/usr/local/lib -Wl,-rpath=/usr/local/lib
    endif
endif
# ----------------------------------------

# Automatically find all .cpp files in the directory
SRC      := $(wildcard *.cpp)
# Replace .cpp extensions with .o for object files
OBJ      := $(SRC:.cpp=.o)

# Default rule when you just type 'make'
all: $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Rule to compile .cpp files into .o (object) files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up compiled files
clean:
	$(RM) $(OBJ) $(TARGET)

# Phony targets aren't actual files
.PHONY: all clean