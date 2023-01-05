# Makefile for building to run on your laptop/desktop

CC = gcc
CCFLAGS = -Wall -O1

# We don't touch the io_hw.cpp or io_hw.h files
SRCS := battleship.cpp io.cpp

bs : $(SRCS)
	$(CC) $(CCFLAGS) -o $@ $^

clean :
	rm -f bs   # delete (native) executable
	rm -f *~   # delete emacs backup files
