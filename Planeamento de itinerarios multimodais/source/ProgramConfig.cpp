#include "ProgramConfig.h"
#include <boost/algorithm/string.hpp>
#include <string>

using namespace std;

void ProgramConfig::getFromConsole()
{
	string answer = "";

	cout << "==> Do you wish to access internal features such as algorithm choice and performance? (Y/N) : ";
	cin >> answer;
	while(answer.size() != 1 || (toupper(answer[0]) != 'N' && toupper(answer[0]) != 'Y'))
	{
		cout << "Invalid answer. Must be Y/N : ";
		cin >> answer;
	}

	if(answer == "N")
	{
		this->runMode = NormalUser;
		return;
	}

	cout << endl << "==> Do you wish to compare all algorithm's performance? (Y/N) : ";
	cin >> answer;
	while(answer.size() != 1 || (toupper(answer[0]) != 'N' && toupper(answer[0]) != 'Y'))
	{
		cout << "Invalid answer. Must be Y/N : ";
		cin >> answer;
	}

	if(answer == "Y")
	{
		this->runMode = AllAlgorithms;
		return;
	}
	else
		this->runMode = Advanced;

	cout << endl << "==> What algorithm do you wish to use?" << endl;
	cout << " 1 - Dijkstra" << endl;
	cout << " 2 - AStar" << endl;
	cout << "Option: ";
	cin >> answer;

	while(answer != "1" && answer != "2")
	{
		cout << "Invalid option. New option: ";
		cin >> answer;
	}

	if(answer == "1")
		this->algorithm = Dijkstra;
	else if(answer == "2")
		this->algorithm = AStar;

	cout << endl << "==> What data structure do you wish to use?" << endl;
	cout << " 1 - Vector" << endl;
	cout << " 2 - Fibonacci Heap" << endl;
	cout << "Option: ";
	cin >> answer;

	while(answer != "1" && answer != "2")
	{
		cout << "Invalid option. New option: ";
		cin >> answer;
	}

	if(answer == "1")
		this->dataStructure = Vector;
	else if(answer == "2")
		this->dataStructure = FibonacciHeap;

}
