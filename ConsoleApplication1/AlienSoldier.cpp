#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(double h, double pw, double AC, int tj): Unit(h, pw, AC, tj)
{
	settype(3);
}

void AlienSoldier::Attack()
{
}
