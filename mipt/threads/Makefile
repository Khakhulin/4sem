CFLAGS = -Wall -g -pthread

all:test_th

test_th: thread_test.o
	gcc  $(CFLAGS) -o $@ $^
%.o:%.c
	gcc -c  $(CFLAGS)  -o $@ $<
clean:
	rm -rf *.o
.PHONY: all clean
