# the compiler
CC = gcc 

# flags
CCFLAGS = -g -Wall
CCFLAGS_NOLINK = -c

INCPATH = -I.

# linking information 
LDFLAGS = -lglut -lGLU -lGL 

# the build target executable
TARGET = main

# the data-file name
FILENAME = "data.dat"

# targets
all: $(TARGET)

$(TARGET): $(TARGET).c fileReader.o polygonsClipper.o
	$(CC) $(INCPATH) $(CCFLAGS) $(TARGET).c fileReader.o utility.o polygonsClipper.o -o output.out $(LDFLAGS)

polygonsClipper.o: polygonsClipper.c polygonsClipper.h structs.h utility.o 
	$(CC) $(INCPATH) $(CCFLAGS) $(CCFLAGS_NOLINK) polygonsClipper.c -o polygonsClipper.o

utility.o: utility.c utility.h structs.h
	$(CC) $(INCPATH) $(CCFLAGS) $(CCFLAGS_NOLINK) utility.c -o utility.o 

fileReader.o: fileReader.c fileReader.h structs.h
	$(CC) $(INCPATH) $(CCFLAGS) $(CCFLAGS_NOLINK) fileReader.c -o fileReader.o

# to run the program
run: 
	./output.out $(FILENAME)

# To start over from scratch,we can type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files.
clean: 
	$(RM) $(TARGET) *.o *.out *~