# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra

# Source files
SRCS := main.cpp Course.cpp Student.cpp System.cpp

# Header files
HDRS := Course.h Student.h System.h

# Object files
OBJS := $(SRCS:.cpp=.o)

# Executable name
EXEC := main

# Rule to compile .cpp files into .o files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to link object files into executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean

# Clean command to remove object files and executable
clean:
	rm -f $(OBJS) $(EXEC)
