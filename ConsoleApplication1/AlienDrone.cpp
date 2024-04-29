#include "AlienDrone.h"



AlienDrone::AlienDrone(double h, double pw, double AC, int tj):Unit(h,pw,AC,tj)
{
	settype(5);
}

void AlienDrone::Attack(Unit*& as)
{
	int damage = (getPower() * getHealth() / 100) / sqrt(as->getHealth());
	as->setHealth(as->getHealth() - damage);
}
