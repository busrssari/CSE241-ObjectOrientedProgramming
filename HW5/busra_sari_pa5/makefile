CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCS = main.cpp FieldProperties.cpp Field.cpp FieldsForTypes.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
