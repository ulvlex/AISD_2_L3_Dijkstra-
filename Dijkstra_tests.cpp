#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab3_Dijkstra/Dijkstra.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Dijkstratests
{
	TEST_CLASS(Dijkstratests)
	{
	public:
		TEST_METHOD(ConsrtructorCustomPairTest) {
			Pair<int, string> MyCustomPair(0, "j");
			Assert::IsTrue(MyCustomPair.getFirst() == 0);
			Assert::IsTrue(MyCustomPair.getSecond() == "j");
		}
		TEST_METHOD(lowestCostTest) {
			Dijkstra MyDijkstraGraphs(3);
			Pair<string, int> city1("A", 0);
			Pair<string, int> city2("B", 1);
			Pair<string, int> city3("C", 2);
			MyDijkstraGraphs.addEdge(city1, city3, 5);
			MyDijkstraGraphs.addEdge(city1, city2, 1);
			MyDijkstraGraphs.addEdge(city2, city3, 2);
			Assert::IsTrue(MyDijkstraGraphs.lowestСost(city1, city3) == 3);
		}
		
		TEST_METHOD(CheapestWayTest) {
			Dijkstra MyDijkstraGraphs(3);
			Pair<string, int> city1("A", 0);
			Pair<string, int> city2("B", 1);
			Pair<string, int> city3("C", 2);
			MyDijkstraGraphs.addEdge(city1, city3, 5);
			MyDijkstraGraphs.addEdge(city1, city2, 1);
			MyDijkstraGraphs.addEdge(city2, city3, 2);
			Assert::IsTrue(MyDijkstraGraphs.cheapestWay(city1, city3) == "A --> B --> C");
			Assert::IsTrue(MyDijkstraGraphs.cheapestWay(city3, city1) == "there is not way from first city to second");
		}
	};
}
