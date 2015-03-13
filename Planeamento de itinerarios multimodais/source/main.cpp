#include "Map.h"
#include "include/SDL2/SDL.h"

using namespace std;

double resize(double x, double minX, double maxX, double minScreen, double maxScreen)
{
	return ((x - minX) / (maxX - minX)) * (maxScreen - minScreen) + minScreen;
}

int main(int argc, char *argv[])
{
	Map map;
	map.load();


	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF );

	double minLat = 999, minLong = 999, maxLat = -999, maxLong = -999;

	BusRoute busRoute = map.getBusRoutes()[0];
	const vector<BusLine> &busLines = busRoute.getBusLines();
	for (size_t i = 0; i < busLines.size(); ++i)
	{
		for (size_t j = 0; j < busLines[i].getLine().size(); ++j)
		{
			if (minLat > busLines[i].getLine()[j].getLatitude())
				minLat = busLines[i].getLine()[j].getLatitude();
			if (minLong > busLines[i].getLine()[j].getLongitude())
				minLong = busLines[i].getLine()[j].getLongitude();
			if (maxLat < busLines[i].getLine()[j].getLatitude())
				maxLat = busLines[i].getLine()[j].getLatitude();
			if (maxLong < busLines[i].getLine()[j].getLongitude())
				maxLong = busLines[i].getLine()[j].getLongitude();
		}
	}

	for (size_t i = 0; i < busLines.size(); ++i)
	{
		for (size_t j = 1; j < busLines[i].getLine().size(); ++j)
		{
			Coordinates coord = busLines[i].getLine()[j];
			Coordinates coord2 = busLines[i].getLine()[j - 1];
			SDL_RenderDrawLine(ren, resize(coord.getLongitude(), minLong, maxLong, 0, 640),
					resize(coord.getLatitude(), minLat, maxLat, 0, 480),
					resize(coord2.getLongitude(), minLong, maxLong, 0, 640),
					resize(coord2.getLatitude(), minLat, maxLat, 0, 480));
			SDL_RenderPresent(ren);
			//SDL_Delay(3);
		}
	}

	SDL_Event Events;    //The SDL event that we will poll to get events.

	while (true)
	{
		SDL_PollEvent(&Events);
		if( Events.type == SDL_QUIT )
		{
			//Quit the program
			break;
		}
	}

	SDL_Quit();
	return 0;
}


