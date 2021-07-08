#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Graph.h"
#include "Node.h"

class SessionManager
{

public:
	SessionManager();
	~SessionManager();
	void Session();
	//void SessionTwo(long source, long destionation, std::vector<std::vector<std::pair<long, long>>>listOfAdjacency);
	//void test();

private:
	// Window
	sf::RenderWindow* window;
	sf::RenderWindow* window2;
	sf::Vector2i windowPosition, windowPosition1;
	sf::Vector2u windowSize, windowSize1;
	std::vector<sf::CircleShape> circles;

	Graph graf;
	std::vector <Node> nodes;
	
};

