#include "Gunnery.h"

Gunnery::Gunnery(double h, double pw, double AC, int tj) : Unit(h, pw, AC, tj)
{
	settype(3);
}

void Gunnery::Attack()
{
}
