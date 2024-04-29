#include "EarthSoldier.h"

EarthSoldier::EarthSoldier(double h, double pw, double AC, int tj): Unit(h, pw, AC, tj)
{
	settype(1);
}

void EarthSoldier::Attack()
{
}
