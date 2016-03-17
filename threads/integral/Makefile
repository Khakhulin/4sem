CC = gcc
CFLAGS =  -O2  -g -Wall   -pthread


SOURCES = paral_int.c
OBJECTS = $(SOURCES:.c = .o)
EXECUTABLE = paral

all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS)  -o $@ $^ -lm
%.o:%.c
	$(CC) -c -MD $(CFLAGS)  -o $@ $<

-include "*.d"
clean:
	rm -f *.o *.d main.out
.PHONY: all clean
