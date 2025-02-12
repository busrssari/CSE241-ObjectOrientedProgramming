CC = g++
CFLAGS = -std=c++11 -Wall
LDFLAGS =

# Kaynak dosyaları
SRCDIR = .
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/robot.cpp $(SRCDIR)/war.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Başlık dosyaları
INCDIR = include
INCLUDES = -I$(INCDIR)

# Çıktı dosyası
EXECUTABLE = main

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $@ $(LDFLAGS)

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
