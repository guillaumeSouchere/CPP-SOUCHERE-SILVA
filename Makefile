CC=g++
CFLAGS=  -Wall -g
LNFLAGS= -lSDL -lSDL_image -lSDL_mixer -std=c++11
SRC=$(wildcard src/*.cpp)
HEAD=$(wildcard src/*.hpp)
OBJ=$(SRC:.cpp=.o)
EXE=game

all: $(OBJ) $(HEAD)
	@echo "link $(EXE)"
	@$(CC) $(OBJ) $(CFLAGS) $(LNFLAGS) -o$(EXE)

src/background.o: src/background.cpp src/background.h src/game.h src/config.h \
 src/timer.h
src/bullet.o: src/bullet.cpp src/bullet.h src/game.h src/config.h src/timer.h
src/character.o: src/character.cpp src/game.h src/config.h src/timer.h \
 src/character.h
src/fog.o: src/fog.cpp src/fog.h src/game.h src/config.h src/timer.h
src/main.o: src/main.cpp src/game.h src/config.h src/timer.h src/character.h \
 src/music.h src/fog.h src/background.h
src/music.o: src/music.cpp src/game.h src/config.h src/timer.h src/music.h
src/timer.o: src/timer.cpp src/timer.h src/game.h src/config.h
src/util.o: src/util.cpp src/game.h src/config.h src/timer.h


clean:
	rm -f src/*.o
	rm -f $(EXE)

.cpp.o:
	@echo "   cc $<"
	@${CC} -c ${CFLAGS} ${LNFLAGS} $< -o $@



