#include "ReachabilityCluster.h"

#include <SFML/Graphics.hpp>
#include <sstream>

#include "Link.h"
#include "Agent.h"

namespace {
	static const int CLUSTER_SIZE = 10;
	static const float FCLUSTER_SIZE = static_cast<float>(CLUSTER_SIZE);
}

// --------------------------------------------------------
// ReachabilityCluster
// --------------------------------------------------------
ReachabilityCluster::ReachabilityCluster(int parMinX, int parMaxX, int parMinY, int parMaxY)
	: FMinX(parMinX)
	, FMaxX(parMaxX)
	, FMinY(parMinY)
	, FMaxY(parMaxY)
{
}

void ReachabilityCluster::Draw(sf::RenderWindow& app) const
{
	sf::Vector2f size(10.0f, 10.0f);
	float decal =  FCLUSTER_SIZE / 2;

	for (auto const & link : FLinks)
	{
		sf::RectangleShape rect(size);
		sf::Vector2f linkPos(link->x * FCLUSTER_SIZE, link->y * FCLUSTER_SIZE);
		rect.setPosition(linkPos.x, linkPos.y);
		rect.setFillColor(sf::Color::Blue);
		app.draw(rect);

		linkPos.x += decal;
		linkPos.y += decal;
		for (auto const & connectedLink : link->ReachableLinks)
		{
			sf::VertexArray lines(sf::LinesStrip, 2);
			lines[0].position = sf::Vector2f(linkPos.x, linkPos.y);
			lines[1].position = sf::Vector2f(connectedLink.link->x * FCLUSTER_SIZE + decal, connectedLink.link->y * FCLUSTER_SIZE + decal);
			app.draw(lines);
		}

		for (auto const & connectedAgent : link->ReachableAgents)
		{
			sf::VertexArray lines(sf::LinesStrip, 2);
			lines[0].position = sf::Vector2f(linkPos.x, linkPos.y);
			lines[1].position = sf::Vector2f(connectedAgent.agent->X() * FCLUSTER_SIZE + decal, connectedAgent.agent->Y() * FCLUSTER_SIZE + decal);
			app.draw(lines);

			/*sf::Vector2f positionText((linkPos.x + connectedAgent.agent->X() * FCLUSTER_SIZE + decal) / 2,
				(linkPos.y + connectedAgent.agent->Y() * FCLUSTER_SIZE + decal) / 2);
			std::stringstream oss;
			oss << connectedAgent.dist;
			sf::Font font;
			font.loadFromFile("../font/arial.ttf");
			sf::Text txt(oss.str(), font, 10);
			txt.setPosition(positionText);
			app.draw(txt);*/
		
		}
	}
}
