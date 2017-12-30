CC = g++
LIB = -lSDL2 -lSDL2_image -lsdl2_mixer -lSDL2_ttf -I/Users/paulcohn/scrapbox/tmxparser/src -I/Users/paulcohn/scrapbox/tmxparser/build -L/Users/paulcohn/scrapbox/tmxparser/build -ltmxparser

game.o: src/main.cpp
	$(CC) src/main.cpp -Wall $(LIB) -o game
		#-framework SDL2 -I/Library/Frameworks/SDL2.framework/Headers/ \
			#-I/Library/Frameworks/SDL2_image.framework/Headers/ \
			#-I/Library/Frameworks/SDL2_ttf.framework/Headers/
