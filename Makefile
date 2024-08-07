CXX = g++
CXXFLAGS = -g -O3
PATH_INCLUDE = include
SFML_INCLUDE = 
SFML_LIBRARY = 
LIBRARIES =  -lsfml-graphics-s -lsfml-audio-s -lsfml-window-s -lsfml-system-s \
			    -lopengl32 -lfreetype -lwinmm -lgdi32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg

all: main clean
clean:
	rm *.o
main: main.o Utils.o
	$(CXX) $(CXXFLAGS) $^ -o $@.exe -L ${SFML_LIBRARY} ${LIBRARIES}

main.o:
	$(CXX) $(CXXFLAGS) -c src/main.cpp -DSFML_STATIC -I$(PATH_INCLUDE) -I${SFML_INCLUDE}

Utils.o:
	$(CXX) $(CXXFLAGS) -c src/Utils.cpp -DSFML_STATIC -I$(PATH_INCLUDE) -I${SFML_INCLUDE}

.PHONY: all clean