#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "../ProgramConfig.h"
#include "../graph/Graph.h"
#include "../graph/Path.h"
#include "../graph/Vertex.h"
#include "AStar.h"
#include "Dijsktra.h"
#include "BruteForce.h"

class PathFinder{

public:
	static Path* find_path(Graph *g, Vertex* ini, Vertex* f, ProgramConfig conf)
	{
		RunningMode r = conf.runningMode();
		switch(r)
		{
		case NormalUser:
			return find_path_normal(g, ini, f, conf);
		case Advanced:
			return find_path_advanced(g, ini, f, conf);
		case AllAlgorithms:
			return find_path_all(g, ini, f, conf);
		}

		return NULL;
	}

private:
	static Path* find_path_normal(Graph *g, Vertex* ini, Vertex* f, ProgramConfig conf)
	{
		return astar_fib(g, ini, f);
	}

	static Path* find_path_advanced(Graph *g, Vertex* ini, Vertex* f, ProgramConfig conf)
	{
		Path *p = new Path(0);
		double ini_d, fin_d;

		switch(conf.desiredAlgorithm())
		{
		case Dijkstra:
		{
			if(conf.desiredDataStructure() == List)
			{
				ini_d = GetTickCount();
				p = dijsktra_list(g, ini, f);
				fin_d = GetTickCount();
			}
			else if (conf.desiredDataStructure() == FibonacciHeap)
			{
				ini_d = GetTickCount();
				p = dijsktra_fib(g, ini, f);
				fin_d = GetTickCount();
			}
			break;
		}
		case AStar:
		{
			if(conf.desiredDataStructure() == List)
			{
				ini_d = GetTickCount();
				p = astar_list(g, ini, f);
				fin_d = GetTickCount();
			}
			else if (conf.desiredDataStructure() == FibonacciHeap)
			{
				ini_d = GetTickCount();
				p = astar_fib(g, ini, f);
				fin_d = GetTickCount();
			}
			break;
		}
		case BruteForce:
		{
			ini_d = GetTickCount();
			p = brute_force(g, ini, f);
			fin_d = GetTickCount();
			break;
		}
		}

		if(conf.wantsAlgorithmPerformance())
		{
			cout << " Algorithm run-time (ms) : " << fixed << setprecision(20) << setw(20) << (double)(fin_d-ini_d) << endl;
		}

		return p;
	}

	static Path* find_path_all(Graph *g, Vertex* ini, Vertex* f, ProgramConfig conf)
	{
		double ini_d, fin_d;
		Path* p;

		ini_d = GetTickCount();
		brute_force(g, ini, f);
		fin_d = GetTickCount();
		cout << " Brute force run-time (ms) : " << fixed << setprecision(20) << setw(20) << (double)(fin_d-ini_d) << endl;

		ini_d = GetTickCount();
		dijsktra_list(g, ini, f);
		fin_d = GetTickCount();
		cout << " Dijkstra run-time using List (ms) : " << fixed << setprecision(20) << setw(20) << (double)(fin_d-ini_d) << endl;

		ini_d = GetTickCount();
		dijsktra_fib(g, ini, f);
		fin_d = GetTickCount();
		cout << " Dijkstra run-time using Fibonacci Heap (ms) : " << fixed << setprecision(20) << setw(20) << (double)(fin_d-ini_d) << endl;

		ini_d = GetTickCount();
		astar_list(g, ini, f);
		fin_d = GetTickCount();
		cout << " A* run-time using List (ms) : " << fixed << setprecision(20) << setw(20) << (double)(fin_d-ini_d) << endl;

		ini_d = GetTickCount();
		p = astar_fib(g, ini, f);
		fin_d = GetTickCount();
		cout << " A* run-time using Fibonacci Heaps (ms) : " << fixed << setprecision(20) << setw(20) << (double)(fin_d-ini_d) << endl;

		return p;
	}
};


#endif
