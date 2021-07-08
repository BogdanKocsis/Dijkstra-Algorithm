#include "SessionManager.h"
#include "Graph.h"
#include <iostream>

SessionManager::SessionManager()
{
	//const sf::VideoMode desktopVM = sf::VideoMode().getDesktopMode();
	const sf::VideoMode windowedVM = sf::VideoMode(980, 960);

	window = new sf::RenderWindow(windowedVM, "Luxembourg1");
	//window= new sf::RenderWindow(desktopVM, "Luxembourg1");



	windowPosition = window->getPosition();
	windowSize = window->getSize();


}

SessionManager::~SessionManager()
{
	delete window;
}

void SessionManager::Session()
{



	std::vector<long>p;
	std::vector<long> path;
	std::vector<std::vector<std::pair<long, long>>>listOfAdjacency;
	bool displey = false;
	nodes = graf.LoadcoordinatesfromXML("map2.xml", listOfAdjacency);


	sf::VertexArray redLines(sf::LinesStrip);
	sf::CircleShape shape(50);
		// run the program as long as the window is open
	window->setActive(true);
	while (window->isOpen())
	{
		
	
		sf::Event event;
		while (window->pollEvent(event))
		{
			


			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;

			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && circles.size() < 2)
			{
				sf::CircleShape circle{ 5 };
				circle.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window)));
				circle.setFillColor(sf::Color::Red);
				circles.push_back(circle);

			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
			{
				sf::Vector2f start_position;
				sf::Vector2f final_position;
				long source, destination;
				if (circles.size())
				{
					start_position.x = circles[0].getPosition().x;
					start_position.y = circles[0].getPosition().y;
					final_position.x = circles[1].getPosition().x;
					final_position.y = circles[1].getPosition().y;

					Node node1(0, circles[0].getPosition().x, circles[0].getPosition().y);

					source = graf.GetClosestIndex(node1, nodes);
					Node node2(0, circles[1].getPosition().x, circles[1].getPosition().y);
					destination = graf.GetClosestIndex(node2, nodes);
					std::cout <<"Source:" <<source << "\n" <<"Destination:"<< destination << "\n";
				}



				p = graf.Dijkstra(listOfAdjacency, source);
				path = graf.Path(p, destination);



				redLines.resize(path.size());
			
				long k = 0;
				for (long long index1 = 0; index1 < path.size(); ++index1)
				{
					redLines[k].position = sf::Vector2f(nodes[path[index1]].GetX(), nodes[path[index1]].GetY());
					redLines[k].color = sf::Color::Red;
					k++;

				}
				displey = true;
			

			}


		}


		sf::VertexArray Points(sf::Points, 42314);

		for (long long index1 = 0; index1 < 42314; ++index1)
		{
			Points[index1].position = sf::Vector2f(nodes[index1].GetX(), nodes[index1].GetY());
		}

		long k = 0;
		sf::VertexArray lines(sf::Lines, 200716);
		for (long long index1 = 0; index1 < 42314; ++index1)
		{


			for (long long j = 0; j < listOfAdjacency[index1].size(); ++j)
			{

				lines[k].position = sf::Vector2f(nodes[index1].GetX(), nodes[index1].GetY());
				k++;
				lines[k].position = sf::Vector2f(Points[listOfAdjacency[index1][j].first].position.x, Points[listOfAdjacency[index1][j].first].position.y);

				k++;
			}
		}



		window->clear();
	
		window->draw(lines);
		for (const auto& c : circles)
			window->draw(c);




		if(displey==true)
		window->draw(redLines);


	
		window->display();


	}
}

