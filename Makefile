LIBS=-lGL -lglut -lGLEW
CC=g++

SOURCES=main_file.cpp tga.cpp detailed_cube.cpp
HEADERS=tga.h cube.h detailed_cube.h
OBJECTS=$(SOURCES:.cpp=.o)

all: main_file

main_file: $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp $(HEADERS)
	$(CC) -c $< -o $@
	
clean:
	-rm -rf *.o main_file
