#include "ProgramConfig.h"
#include <string>
#include "WeightInfo.h"

using namespace std;

double readDouble()
{
	double temp;
	cin >> temp;
	while(cin.fail())
	{
		cout << "Invalid value. New value : ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> temp;
	}
	return temp;
}

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

	if(toupper(answer[0]) == 'N')
	{
		this->runMode = NormalUser;
	}
	else
	{
		cout << endl << "==> Do you wish to compare all algorithm's performance? (Y/N) : ";
		cin >> answer;
		while(answer.size() != 1 || (toupper(answer[0]) != 'N' && toupper(answer[0]) != 'Y'))
		{
			cout << "Invalid answer. Must be Y/N : ";
			cin >> answer;
		}

		if(toupper(answer[0]) == 'Y')
		{
			this->runMode = AllAlgorithms;
		}
		else
		{
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
			cout << " 1 - List" << endl;
			cout << " 2 - Fibonacci Heap" << endl;
			cout << "Option: ";
			cin >> answer;

			while(answer != "1" && answer != "2")
			{
				cout << "Invalid option. New option: ";
				cin >> answer;
			}

			if(answer == "1")
				this->dataStructure = List;
			else if(answer == "2")
				this->dataStructure = FibonacciHeap;
		}
	}

	double timeCost, distCost, moneyCost, transbordCost;

	cout << endl << endl << " In order to calculate the best path, you must indicate the relative cost of each parameter." << endl
			<< "In other words, you must associate a monetary cost to each parameter, representing how much you value it." << endl
			<< "For example, if you value time a lot (you want the fastest route), give each minute a value of 200 (for example)." << endl;

	cout << endl << "==> Please insert your values for time, distance, monetary cost and number of transport changes:" << endl;
	cout << " 1 - Time (cost per minute) : ";
	timeCost = readDouble();
	cout << " 2 - Monetary cost (cost per euro) : ";
	moneyCost = readDouble();
	cout << " 3 - Distance cost (cost per meter) : ";
	distCost = readDouble();
	cout << " 4 - Cost per number of transport changes : ";
	transbordCost = readDouble();

	WeightInfo::setTimeWeight(timeCost);
	WeightInfo::setCostWeight(moneyCost);
	WeightInfo::setDistanceWeight(distCost);
	WeightInfo::setSwitchWeight(transbordCost);
}
