CC=g++
CFLAGS=-c -Wall -std=c++14 -pg
LDFLAGS=-pg
LIBS = -lfftw3 -lm

MAINSRC=inplace_r2c_Poisson_example.cpp
SOURCES=$(MAINSRC)

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=poisson.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(HEADERS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

.cpp.o: $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o *.exe
