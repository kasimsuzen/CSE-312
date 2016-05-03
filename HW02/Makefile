CC= g++
CFLAGS= -c -Wall -std=c++11
LDFLAGS=
SOURCES= main.cpp Memory.cpp Instruction.cpp Process.cpp CPU.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= Simulate.exe

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f *.o core *.core $(EXECUTABLE)