# Makefile for the Java project

# Variables
JFLAGS = -g
JC = javac
JVM = java
SRC_DIR = .
CLASSES_DIR = ../classes

# Find all Java source files
SOURCES = $(shell find $(SRC_DIR) -name '*.java')

# Create list of class files
CLASSES = $(SOURCES:$(SRC_DIR)/%.java=$(CLASSES_DIR)/%.class)

# Default target
default: classes

# Compile all Java files
$(CLASSES_DIR)/%.class: $(SRC_DIR)/%.java
	@mkdir -p $(dir $@)
	$(JC) $(JFLAGS) -d $(CLASSES_DIR) $<

classes: $(CLASSES)

run: classes
	$(JVM) -cp $(CLASSES_DIR) Main

clean:
	rm -rf $(CLASSES_DIR)
