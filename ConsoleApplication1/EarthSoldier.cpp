#include "EarthSoldier.h"

EarthSoldier::EarthSoldier(double h, double pw, double AC, int tj): Unit(h, pw, AC, tj)
{
	settype(0);
}

void EarthSoldier::Attack(Unit*&as)
{
	int damage = (getPower() * getHealth() / 100) / sqrt(as->getHealth());
	as->setHealth(as->getHealth() - damage);
}
