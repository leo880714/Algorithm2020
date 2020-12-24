# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
OPTFLAGS = -O3

all	: bin/mps
	@echo -n ""

# optimized version
bin/mps	: mps_function.o main_opt.o
			$(CC) $(OPTFLAGS) mps_function.o main_opt.o -o bin/mps
main_opt.o 	   	: src/main.cpp src/mpsfunction.h
			$(CC) $(CFLAGS) $< -o $@
mps_function.o	: src/mpsfunction.cpp src/mpsfunction.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*

