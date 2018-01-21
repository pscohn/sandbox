CC = g++
CFLAGS=-c -I/Users/paulcohn/scrapbox/tmxparser/src -I/Users/paulcohn/scrapbox/tmxparser/build \
	-I./src

LIB = -lSDL2 -lSDL2_image -lsdl2_mixer -lSDL2_ttf \
			-ltmxparser \
			-ltinyxml2 \
			-L/Users/paulcohn/scrapbox/tmxparser/build \
			-L/Users/paulcohn/scrapbox/tinyxml2 \
			-lfluidsynth

#all: game

ok: main.o game.o piano.o
	$(CC) -Wall $(LIB) -o ok main.o game.o piano.o

# game.o: src/main.cpp src/game.cpp
# 	$(CC) src/main.cpp src/game.cpp src/piano.cpp -Wall $(LIB) -o game
		#-framework SDL2 -I/Library/Frameworks/SDL2.framework/Headers/ \
			#-I/Library/Frameworks/SDL2_image.framework/Headers/ \
			#-I/Library/Frameworks/SDL2_ttf.framework/Headers/


main.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp
#	$(CC) src/main.cpp -Wall $(LIB) -o game main.o game.o
#	$(CC) src/main.cpp -Wall $(LIB) -o game game.o
		#-framework SDL2 -I/Library/Frameworks/SDL2.framework/Headers/ \
			#-I/Library/Frameworks/SDL2_image.framework/Headers/ \
			#-I/Library/Frameworks/SDL2_ttf.framework/Headers/

#
game.o: src/game.cpp
	$(CC) $(CFLAGS) src/game.cpp

piano.o: src/piano.cpp
	$(CC) $(CFLAGS) src/piano.cpp
