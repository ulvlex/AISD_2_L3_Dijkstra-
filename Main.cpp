#include "Dijkstra.h"
#include <fstream>

using namespace std;

string fileName = "cities.txt";
string A = "NYC";
string B = "Mexico";

int main() {

	List<string> CityList;
	Map<string, int> CityMap;

	string oneString;
	string FirstCityName = "";
	string SecondCityName = "";
	string bufCost = "";
	int cost = 0;

	//Read cities

	cout << "Cities:\n\n";
	ifstream file_input;
	file_input.open(fileName);

	while (!file_input.eof()) {
		getline(file_input, oneString);
		cout << oneString << endl;

		//First
		FirstCityName = oneString.substr(0, oneString.find(';'));
		if (!CityList.check(FirstCityName)) {
			CityMap.insert(FirstCityName, CityList.get_size());
			CityList.push_back(FirstCityName);
		}
		oneString.erase(0, oneString.find(';') + 1);

		//Second
		SecondCityName = oneString.substr(0, oneString.find(';'));
		if (!CityList.check(SecondCityName)) {
			CityMap.insert(SecondCityName, CityList.get_size());
			CityList.push_back(SecondCityName);
		}

		//Skip it
		oneString.erase(0, oneString.find(';') + 1);
		oneString.erase(0, oneString.find(';') + 1);
	}
	file_input.close();

	Dijkstra NewDijkstra(CityList.get_size());

	file_input.open(fileName);
	while (!file_input.eof()) {
		getline(file_input, oneString);

		//Skip it
		FirstCityName = oneString.substr(0, oneString.find(';'));
		oneString.erase(0, oneString.find(';') + 1);
		SecondCityName = oneString.substr(0, oneString.find(';'));
		oneString.erase(0, oneString.find(';') + 1);

		//Cost To
		bufCost = oneString.substr(0, oneString.find(';'));
		if (bufCost != "N/A") {
			cost = stoi(bufCost);
			NewDijkstra.addEdge(Pair<string, int>(CityMap.find(FirstCityName)->key, CityMap.find(FirstCityName)->value), Pair<string, int>(CityMap.find(SecondCityName)->key, CityMap.find(SecondCityName)->value), cost);
		}
		oneString.erase(0, oneString.find(';') + 1);

		//Cost From
		bufCost = oneString.substr(0, oneString.find(';'));
		if (bufCost != "N/A") {
			cost = stoi(bufCost);
			NewDijkstra.addEdge(Pair<string, int>(CityMap.find(SecondCityName)->key, CityMap.find(SecondCityName)->value), Pair<string, int>(CityMap.find(FirstCityName)->key, CityMap.find(FirstCityName)->value), cost);
		}
	}
	file_input.close();

	//Main work with algorithm

	cout << "\nRBTree of cities: \n" << endl;
	CityMap.print();

	//There
	string city_from = A;
	string city_to = B;

	cout << "\n\nThe path with the least cost from" << city_from << " to " << city_to << ":" << endl;
	cout << NewDijkstra.cheapestWay(Pair<string, int>(CityMap.find(city_from)->key, CityMap.find(city_from)->value), Pair<string, int>(CityMap.find(city_to)->key, CityMap.find(city_to)->value)) << endl;

	cout << "Cost is: ";
	try {
		cout << NewDijkstra.lowestÑost(Pair<string, int>(CityMap.find(city_from)->key, CityMap.find(city_from)->value), Pair<string, int>(CityMap.find(city_to)->key, CityMap.find(city_to)->value)) <<endl;
	}
	catch (const invalid_argument error) {
		cout << error.what() <<endl;
	}

	//Back
	city_from = B;
	city_to = A;

	cout << "\nThe path with the least cost from" << city_from << " to " << city_to << ":" <<endl;
	cout << NewDijkstra.cheapestWay(Pair<string, int>(CityMap.find(city_from)->key, CityMap.find(city_from)->value), Pair<string, int>(CityMap.find(city_to)->key, CityMap.find(city_to)->value));

	cout << "\nCost is: ";
	try {
		cout << NewDijkstra.lowestÑost(Pair<string, int>(CityMap.find(city_from)->key, CityMap.find(city_from)->value), Pair<string, int>(CityMap.find(city_to)->key, CityMap.find(city_to)->value)) << endl;
	}
	catch (const invalid_argument error) {
		cout << error.what() <<endl;
	}
}