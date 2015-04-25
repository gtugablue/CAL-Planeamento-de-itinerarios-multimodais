#ifndef PROGRAM_COFIG_H
#define PROGRAM_COFIG_H

#include "transport/WeightInfo.h"
#include <iostream>

enum Algorithm { Dijkstra, AStar, BruteForce };
enum DataStructure { List, FibonacciHeap };
enum RunningMode { NormalUser, Advanced, AllAlgorithms };

/*
 * NormalUser - does not take part in algorithm choice or any "technical" issues related to the program's purpose.
 * 				He only chooses the start and exit point on the map
 * Advanced   - does everything the NormalUser does, but can also choose what kind of algorithm or data structure the program
 * 				must use, and can enable the viewing of that algorithm's performance
 * AllAlgorithms - does everything the AdvancedUser does, but runs the program through all algorithms to compare their performances
 */

class ProgramConfig{

public:

	bool wantsAlgorithmPerformance() {return wantAlgorithmPerformance;}
	Algorithm desiredAlgorithm() {return algorithm;}
	DataStructure desiredDataStructure() {return dataStructure;}
	RunningMode runningMode() {return runMode;}

	void setWantsAlgorithmPerformance(bool wants) {wantAlgorithmPerformance = wants;}
	void setAlgorithm(Algorithm algorithm) {this->algorithm = algorithm;}
	void setDataStructure(DataStructure dataStructure) {this->dataStructure = dataStructure;}
	void setRunningMode(RunningMode runningMode) {this->runMode = runningMode;}

	void getFromConsole();

	ProgramConfig(): runMode(NormalUser), algorithm(AStar), dataStructure(FibonacciHeap), wantAlgorithmPerformance(false) {}

private:
	bool wantAlgorithmPerformance;
	Algorithm algorithm;
	DataStructure dataStructure;
	RunningMode runMode;
};


#endif
