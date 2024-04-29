#include "AlienMonster.h"

AlienMonster::AlienMonster(double h, double pw, double AC, int tj) : Unit(h, pw, AC, tj)
{
	settype(4);
}

void AlienMonster::Attack(Unit*& as)
{
	int damage = (getPower() * getHealth() / 100) / sqrt(as->getHealth());
	as->setHealth(as->getHealth() - damage);
}
