SDL_LIB = -I./lib/sdl2/include -L./lib/sdl2/lib -lSDL2-2.0.0
SDL_TTF_LIB = -I./lib/sdl2_ttf/include -L./lib/sdl2_ttf/lib -lSDL2_ttf-2.0.0
SRC = app.cpp src/*.cpp src/**/*.cpp

main:
	g++ --std=c++17 $(SRC) -g -pedantic -o build $(SDL_LIB) $(SDL_TTF_LIB)
	./build