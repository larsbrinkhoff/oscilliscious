CFLAGS += -W -Wall -g `sdl2-config --cflags`
LDLIBS += -lm `sdl2-config --libs`

all: test

test: test.o line.o point.o

clean:
	rm test *.o
