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
		SDL_Window *win = SDL_CreateWindow("Autocarros STCP", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
		SDL_Renderer *ren = SDL_CreateRenderer(win, (int)-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF );
		double minLat = 999, minLong = 999, maxLat = -999, maxLong = -999;
		for (size_t i = 0; i < map.getBusRoutes().size(); ++i)
		{
			BusRoute busRoute = map.getBusRoutes()[i];
			const vector<BusEdge> &BusEdges = busRoute.getBusEdges();
			for (size_t j = 0; j < BusEdges.size(); ++j)
			{
				for (size_t k = 0; k < BusEdges[j].getLine().size(); ++k)
				{
					if (minLat > BusEdges[j].getLine()[k].getLatitude())
						minLat = BusEdges[j].getLine()[k].getLatitude();
					if (minLong > BusEdges[j].getLine()[k].getLongitude())
						minLong = BusEdges[j].getLine()[k].getLongitude();
					if (maxLat < BusEdges[j].getLine()[k].getLatitude())
						maxLat = BusEdges[j].getLine()[k].getLatitude();
					if (maxLong < BusEdges[j].getLine()[k].getLongitude())
						maxLong = BusEdges[j].getLine()[k].getLongitude();
				}
			}
		}
		for (size_t i = 0; i < map.getBusRoutes().size(); ++i)
		{
			BusRoute busRoute = map.getBusRoutes()[i];
			const vector<BusEdge> &BusEdges = busRoute.getBusEdges();
			for (size_t j = 0; j < BusEdges.size(); ++j)
			{
				for (size_t k = 1; k < BusEdges[j].getLine().size(); ++k)
				{
					Coordinates coord = BusEdges[j].getLine()[k];
					Coordinates coord2 = BusEdges[j].getLine()[k - 1];
					SDL_RenderDrawLine(ren, resize(coord.getLongitude(), minLong, maxLong, 0, 640),
							480 - resize(coord.getLatitude(), minLat, maxLat, 0, 480),
							resize(coord2.getLongitude(), minLong, maxLong, 0, 640),
							480 - resize(coord2.getLatitude(), minLat, maxLat, 0, 480));
				}
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


