#pragma once
#include <vector>
#include <string>
#include "Node.h"
#include "Edge.h"

class Graph
{

public:
	Graph() = default;
	~Graph() = default;
	std::vector<Node> LoadcoordinatesfromXML(std::string file, std::vector<std::vector<std::pair<long, long>>>& listOfAdjacency);
	std::vector<long> Dijkstra(std::vector<std::vector<std::pair<long, long>>> listOfAdjacency, long source);
	std::vector<long> Path(std::vector<long> p, long destionation);
	long distance(Node n1, Node n2);
	long GetClosestIndex(Node givenNode,std::vector <Node> p);
	void test();

private:

	std::vector<std::vector<std::pair<long, long>>> listOfAdjacency;
	std::vector<long> path;
	long n = 42314;
	long m = 100358;
};

