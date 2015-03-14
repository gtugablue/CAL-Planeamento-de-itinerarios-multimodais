#include "Map.h"
#include "include/SDL2/SDL.h"

using namespace std;

double resize(double x, double minX, double maxX, double minScreen, double maxScreen)
{
	return ((x - minX) / (maxX - minX)) * (maxScreen - minScreen) + minScreen;
}

int main(int argc, char *argv[])
{
	Map::Loader l;
	Map map;
	try
	{
		map = l.load();

		SDL_Init(SDL_INIT_VIDEO);
		SDL_Window *win = SDL_CreateWindow("Linha 201", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
		SDL_Renderer *ren = SDL_CreateRenderer(win, (int)-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF );

		double minLat = 999, minLong = 999, maxLat = -999, maxLong = -999;

		BusRoute busRoute = map.getBusRoutes()[0];
		const vector<BusEdge> &BusEdges = busRoute.getBusEdges();
		for (size_t i = 0; i < BusEdges.size(); ++i)
		{
			for (size_t j = 0; j < BusEdges[i].getLine().size(); ++j)
			{
				if (minLat > BusEdges[i].getLine()[j].getLatitude())
					minLat = BusEdges[i].getLine()[j].getLatitude();
				if (minLong > BusEdges[i].getLine()[j].getLongitude())
					minLong = BusEdges[i].getLine()[j].getLongitude();
				if (maxLat < BusEdges[i].getLine()[j].getLatitude())
					maxLat = BusEdges[i].getLine()[j].getLatitude();
				if (maxLong < BusEdges[i].getLine()[j].getLongitude())
					maxLong = BusEdges[i].getLine()[j].getLongitude();
			}
		}

		for (size_t i = 0; i < BusEdges.size(); ++i)
		{
			for (size_t j = 1; j < BusEdges[i].getLine().size(); ++j)
			{
				Coordinates coord = BusEdges[i].getLine()[j];
				Coordinates coord2 = BusEdges[i].getLine()[j - 1];
				SDL_RenderDrawLine(ren, resize(coord.getLongitude(), minLong, maxLong, 0, 640),
						480 - resize(coord.getLatitude(), minLat, maxLat, 0, 480),
						resize(coord2.getLongitude(), minLong, maxLong, 0, 640),
						480 - resize(coord2.getLatitude(), minLat, maxLat, 0, 480));
			}
		}

		SDL_Event Events;    //The SDL event that we will poll to get events.
		SDL_RenderPresent(ren);
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
	catch (std::fstream::failure e)
	{
		cout << "derpou" << endl;
		std::cerr << e.what();
		return 1;
	}
}


