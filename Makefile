CXX = g++-13
CXXFLAGS = -std=c++17 -I $$PWD/src/include
LDFLAGS = -L $$PWD/src/lib 
LIBS = -lSDL2

all: clean

clean: run
	rm game

run: game
	DYLD_LIBRARY_PATH=$$PWD/src/lib ./game

game: main.cpp Background.cpp
	clear && $(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)
