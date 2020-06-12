SDL_LIB = `/usr/local/Cellar/sdl2/2.0.12_1/bin/sdl2-config --cflags --libs` -lSDL2-2.0.0
SDL_TTF_LIB = -I/usr/local/Cellar/sdl2_ttf/2.0.15/include -L/usr/local/Cellar/sdl2_ttf/2.0.15/lib -lSDL2_ttf-2.0.0
SRC = app.cpp src/*.cpp src/**/*.cpp

main:
	g++ --std=c++17 $(SRC) -g -pedantic -o build $(SDL_LIB) $(SDL_TTF_LIB)
	./build