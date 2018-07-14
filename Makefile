TARGET = shell
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

HEADERS = $(shell find . -name "*.h")
SOURCES = $(shell find . -name "*.c")
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f $(shell find . -name "*.o")
	-rm -f $(TARGET)
