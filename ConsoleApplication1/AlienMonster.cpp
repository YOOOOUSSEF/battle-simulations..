#include "AlienMonster.h"

AlienMonster::AlienMonster(double h, double pw, double AC, int tj) : Unit(h, pw, AC, tj)
{
	settype(5);
}

void AlienMonster::Attack()
{
}
