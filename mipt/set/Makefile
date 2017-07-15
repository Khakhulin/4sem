CC = gcc
CFLAGS =  -O2 -g -Wall  ##-Werror
GCOV_F =  -fprofile-arcs -ftest-coverage


SOURCES = set.c $(EXECUTABLE).c
OBJECTS = $(SOURCES:.c = .o)
EXECUTABLE = test

all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS)  $(GCOV_F) -o $@ $^
%.o:%.c
	$(CC) -c -MD $(CFLAGS) $(GCOV_F) -o $@ $<
-include $(wildcard *.d)
clean:
	rm -f *.o *.d main.out
clean_gcov:
	rm -f *.g*
.PHONY: all clean
