#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(double h, double pw, double AC, int tj): Unit(h, pw, AC, tj)
{
	settype(3);
	
}

void AlienSoldier::Attack(Unit*& as)
{
	int damage = (getPower() * getHealth() / 100) / sqrt(as->getHealth());
	as->setHealth(as->getHealth() - damage);
}
