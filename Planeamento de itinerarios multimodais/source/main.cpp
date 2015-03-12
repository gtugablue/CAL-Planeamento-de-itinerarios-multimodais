#include "Map.h"
#include "include/SDL2/SDL.h"

using namespace std;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF );
	SDL_RenderDrawLine(ren, 0, 0, 100, 100);
	SDL_RenderPresent(ren);

	SDL_Delay(2000);
	SDL_Quit();

	Map map;
	map.load();

	return 0;
}


