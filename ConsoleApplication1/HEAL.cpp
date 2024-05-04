#include "HEAL.h"

HEAL::HEAL(double h, double pw, double AC, int tj) :Unit(h, pw, AC, tj)
{
	settype(6);
}

void HEAL::Attack(Unit*& p) {
	int healthimprovment = (getHealth() * getPower() / 100) * sqrt(p->getHealth());
	p->setHealth(p->getHealth() + healthimprovment);
}
