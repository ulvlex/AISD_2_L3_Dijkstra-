#pragma once
#include <string>
#include  "Map.h"
#include "Pair.h"

using namespace std;

class Dijkstra {

	int cntVertexes; 
	Map<int, string> InverseCitiesMap; // map contains vertexes indexes
	List<Pair<Pair<string, int>, int> >* AdjacencyList;

	int* distance;
	int* bufD;
	bool* visited;

	void dijkstraAlgorithm(Pair<string, int> start, Pair<string, int> finish) {

		for (int i = 0; i < cntVertexes; i++) 
			visited[i] = false;

		for (int i = 0; i < cntVertexes; i++)
			distance[i] = INT_MAX;

		distance[start.getSecond()] = 0;
		for (int i = 0; i < cntVertexes - 1; i++) {
			int minD = minDistance();
			visited[minD] = true;
			auto current = AdjacencyList[minD].head;

			while (current != NULL) {
				if (visited[current->info.getFirst().getSecond()] == false && 
					distance[minD] != INT_MAX && 
					distance[current->info.getFirst().getSecond()] > distance[minD] + current->info.getSecond()) {

					distance[current->info.getFirst().getSecond()] = distance[minD] + current->info.getSecond();
					bufD[current->info.getFirst().getSecond()] = minD;
				}
				current = current->next;
			}
		}

	}

	int minDistance() {

		int min = INT_MAX;
		int index = 0;

		for (int i = 0; i < cntVertexes; i++)
			if (distance[i] <= min && visited[i] == false) {
				min = distance[i];
				index = i;
			}
		return index;

	}

public:
	Dijkstra(const int vertexes) {

		cntVertexes = vertexes;
		AdjacencyList = new List<Pair<Pair<string, int>, int> >[cntVertexes];

		distance = new int[cntVertexes];
		bufD = new int[cntVertexes];
		visited = new bool[cntVertexes];

	}

	~Dijkstra() {

		delete[] AdjacencyList;
		delete[] distance;
		delete[] bufD;
		delete[] visited;
		InverseCitiesMap.~Map();

	}

	void addEdge(Pair<string, int> cityFrom, Pair<string, int> cityTo, int weight) {

		AdjacencyList[cityFrom.getSecond()].push_back(Pair<Pair<string, int>, int>(cityTo, weight));
		InverseCitiesMap.insert(cityFrom.getSecond(), cityFrom.getFirst());
		InverseCitiesMap.insert(cityTo.getSecond(), cityTo.getFirst());

	}

	string cheapestWay(Pair<string, int> start, Pair<string, int> finish) {

		dijkstraAlgorithm(start, finish);

		string result = "";

		if (distance[finish.getSecond()] == INT_MAX) {
			return "there is not way from first city to second";
		}
		else {
			List<string> way;

			for (int v = finish.getSecond(); v != start.getSecond(); v = bufD[v]) {
				way.push_back(InverseCitiesMap.find(v)->value);
			}

			way.push_back(start.getFirst());
			way.reverse();
			auto output = way.head;

			while (output != NULL) {
				result += output->info;
				if (output != way.tail) result += " --> ";
				output = output->next;
			}

			return result;
		}
	}

	int lowest—ost(Pair<string, int> start, Pair<string, int> finish) {

		dijkstraAlgorithm(start, finish);

		if (distance[finish.getSecond()] == INT_MAX) {
			throw invalid_argument("There is not way from first city to second");
		}

		return distance[finish.getSecond()];
	}

};