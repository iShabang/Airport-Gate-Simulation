CC=g++
CFLAGS=-c -Wall -Wextra
SOURCES = heap.h main.cpp myStack.h
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE=CN

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE):$(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
