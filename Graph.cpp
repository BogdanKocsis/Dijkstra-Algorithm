#include "Graph.h"
#import <msxml3.dll>
#include <iostream>
#include <queue>
#include <fstream>
#include "RapidXML/rapidxml-1.13/rapidxml.hpp"
#include <math.h>

#define INFINITE 999999999 

std::vector<Node> Graph::LoadcoordinatesfromXML(std::string file, std::vector<std::vector<std::pair<long, long>>>& listOfAdjacency)
{

	std::vector<Node> nodes;
	std::vector<Node> coordonates;
	std::vector<Edge> edges;
	std::vector<Edge> links;
	long xMax = 0, xMin = 999999999, yMax = 0, yMin = 999999999;
	std::ifstream databaseFile("map2.xml");
	std::string* databaseContent = new std::string((std::istreambuf_iterator<char>(databaseFile)),
		std::istreambuf_iterator<char>());
	rapidxml::xml_document<> xmlDocument;
	xmlDocument.parse<0>(const_cast<char*>(databaseContent->c_str()));

	// Read data on separate threads
	rapidxml::xml_node<>* mainRoot = xmlDocument.first_node("map");
	rapidxml::xml_node<>* root = mainRoot->first_node();

	if (mainRoot->first_node("nodes"))
	{

		rapidxml::xml_node<>* root = mainRoot->first_node("nodes")->first_node("node");
		for (int index1 = 0; index1 < n; ++index1)
		{

			long index, longitude, latitude;
			index = std::stol(root->first_attribute("id")->value());
			longitude = std::stol(root->first_attribute("latitude")->value());
			if (longitude > xMax)
				xMax = longitude;
			if (longitude < xMin)
				xMin = longitude;
			latitude = std::stol(root->first_attribute("longitude")->value());
			if (latitude > yMax)
				yMax = latitude;
			if (latitude < yMin)
				yMin = latitude;
			Node node(index, longitude, latitude);
			nodes.emplace_back(node);
			root = root->next_sibling("node");

		}
	}

	mainRoot = xmlDocument.first_node("map");
	
	if (mainRoot->first_node("arcs"))
	{
		rapidxml::xml_node<>* root = mainRoot->first_node("arcs")->first_node("arc");
		for (int index1 = 0; index1 < m; ++index1)
		{
			long from, to, lenght;
			from = std::stol(root->first_attribute("from")->value());
			to = std::stol(root->first_attribute("to")->value());
			lenght = std::stol(root->first_attribute("length")->value());
			Edge edge(from, to, lenght);
			edges.emplace_back(edge);
			root = root->next_sibling("arc");
		}

	}


	listOfAdjacency.resize(42314);

	int border = 25;
	int Width = 920;
	int Height = 980;
	for (long long index = 0; index <= 42313; ++index)
	{
		long xCoord = border + ((nodes[index].GetX() - xMin) * (Width - 2 * border) / (xMax - xMin));
		long yCoord = border + ((-(nodes[index].GetY() - yMin) + (yMax - yMin)) * (Height - 2 * border) ) / (yMax - yMin);
	
		nodes[index].SetX(xCoord);
		nodes[index].SetY(yCoord);
	}



	
	for (long long index = 0; index < 100358; ++index)
	{
		long source = edges[index].GetSource();
		long destination = edges[index].GetDestination();
		long weight = edges[index].GetWeight();
		listOfAdjacency[source].push_back(std::make_pair(destination, weight));

	}

	std::cout << "XML completed\n";
	return nodes;
}



std::vector<long> Graph::Dijkstra(std::vector<std::vector<std::pair<long, long>>> listOfAdjacency, long source)
{
	std::vector<long> d(n, INFINITE);
	std::vector<long> p(n, INFINITE);
	std::priority_queue < std::pair<long, long>, std::vector < std::pair<long, long >>, std::greater<std::pair<long, long>>> pq;

	pq.push(std::make_pair(source, 0));
	d[source] = -1;
	p[source] = -1;

	while (pq.empty() == false)
	{
		long u = pq.top().first;
		pq.pop();

		for (long index = 0; index < listOfAdjacency[u].size(); ++index)
		{
			long v = listOfAdjacency[u][index].first;
			long weight = listOfAdjacency[u][index].second;
			if (d[v] > d[u] + weight)
			{
				d[v] = d[u] + weight;
				p[v] = u;
				pq.push(std::make_pair(v, d[v]));
			}
		}

	}
	return p;

}

std::vector<long> Graph::Path(std::vector<long> p, long destination)
{
	
	std::vector<long> path;
	for (long v = destination; v != -1; v = p[v])
		path.push_back(v);
	std::reverse(path.begin(), path.end());
	std::cout << "The path is:";
	for (const auto& index : path)
	{
		std::cout << index << " ";
	}
	std::cout << "\n";
	return path;
}

long Graph::distance( Node n1 , Node n2)
{
	return (double)(std::sqrt((n1.GetX() - n2.GetX()) * (n1.GetX() - n2.GetX())
		+ (n1.GetY() - n2.GetY()) * (n1.GetY() - n2.GetY())));
	
}

long Graph::GetClosestIndex(Node givenNode, std::vector<Node>p)
{
	long min = INFINITE, min2 = INFINITE;
	long index1, index2, index;

	long dist = 0;
	Node node = p[0];
	for(auto nod: p)
	{
		
		dist = distance(givenNode, nod);
		if (min > dist)
		{
			min = dist;
			node = nod;
		}

		
	}



	return node.Getindex();

}


void Graph::test()
{
	std::vector <Node> test;
	//std::vector<std::vector<std::pair<long, long>>>listOfAdjacency;
	test = LoadcoordinatesfromXML("map2.xml", listOfAdjacency);
	//std::vector<long> p;
	//p = Dijkstra(listOfAdjacency, 1);
	//path=Path(p, 3412);
	std::cout << "\n";
	for (const auto& index :test)
		std::cout << index.GetX() << " "<<index.GetY()<<"\n";


}
