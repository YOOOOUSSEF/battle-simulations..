#include "EarthTank.h"

EarthTank::EarthTank(double h, double pw, double AC, int tj): Unit(h, pw, AC, tj)
{
	settype(2);
}

void EarthTank::Attack()
{
}
