#include "Gunnery.h"

Gunnery::Gunnery(double h, double pw, double AC, int tj) : Unit(h, pw, AC, tj)
{
	settype(2);
}

void Gunnery::Attack(Unit*&dr_Or_mons)
{
	int damage = (getPower() * getHealth() / 100) / sqrt(dr_Or_mons->getHealth());
	dr_Or_mons->setHealth(dr_Or_mons->getHealth() - damage);
}
