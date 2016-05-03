CC= g++
CFLAGS= -c -Wall -std=c++11
LDFLAGS=
SOURCES= main.cpp MemoryCell.cpp Instruction.cpp Simulation.cpp Disk.cpp PageTableEntry.cpp RAM.cpp PageTable.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= Simulate.exe

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f *.o core *.core $(EXECUTABLE)