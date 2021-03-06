#include <sstream>

#include "Probe.h"

#include "World.h"

BOOST_CLASS_EXPORT_IMPLEMENT(Probe)

Probe::Probe(void)
	: BaseObject("probe")
	, FTemp(0.0f)
{
	FLayer = 1;
	FFont.loadFromFile("../font/arial.ttf");
	FText = sf::Text("", FFont, 7);
	FText.setPosition(FPosition.MinX<float>(), FPosition.MinY<float>());
}


Probe::~Probe(void)
{
}

BaseObject * Probe::Clone() const
{
	return new Probe();
}

void Probe::Draw(sf::RenderWindow & app) const
{
	app.draw(FText);
}

void Probe::Update(World * parWorld)
{
	FTemp = parWorld->GetCelluls()[FPosition.MinY<int>()][FPosition.MinX<int>()].Temp;
	FTemp = ceilf(FTemp * 100.0f) / 100.0f;

	std::ostringstream strText;
	strText << FTemp;
	FText = sf::Text(strText.str(), FFont, 7);
	FText.setPosition(FPosition.MinX<float>() * Config::CellulSize, FPosition.MinY<float>() * Config::CellulSize);
}