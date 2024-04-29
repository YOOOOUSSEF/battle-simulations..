#include "EarthTank.h"

EarthTank::EarthTank(double h, double pw, double AC, int tj): Unit(h, pw, AC, tj)
{
	settype(1);
}

void EarthTank::Attack(Unit*&mons_or_as)
{
	int damage = (getPower() * getHealth() / 100) / sqrt(mons_or_as->getHealth());
	mons_or_as->setHealth(mons_or_as->getHealth() - damage);
}
