# Compiler settings
CXX      := g++
# C++17 is required for std::optional used in SFML 3
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 

# SFML Linker flags (Graphics, Window, and System are standard)
LDFLAGS  := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# The name of your final executable
TARGET   := Sandtris.exe

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
	rm -f $(OBJ) $(TARGET)

# Phony targets aren't actual files
.PHONY: all clean