#pragma once
#include "BaseObject.h"

class WindowObject : public BaseObject
{
public:
	WindowObject(void);
	virtual ~WindowObject(void);

	virtual void Draw(sf::RenderWindow & app) const;
	virtual BaseObject * Clone() const;
	virtual void Update(World * parWorld);
	virtual bool OnClick(World * parWorld, int parX, int parY);

	void SetEnable(bool parValue) { FEnable = parValue; }
	bool Enable() const { return FEnable; }

	friend class boost::serialization::access;
	template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(BaseObject);
		ar & FEnable;
    }

	virtual void CreateAgent(SMAHeat & parSMA)
	{
		parSMA.CreateAgent(*this);
	}
private:
	bool FEnable;
};

BOOST_CLASS_EXPORT_KEY(WindowObject);
