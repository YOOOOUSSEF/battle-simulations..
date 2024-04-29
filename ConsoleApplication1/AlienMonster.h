#pragma once
#include"Unit.h"
class AlienMonster:public Unit
{
public:
	
 AlienMonster(double h=0, double pw=0, double AC=0, int tj=0);
 void Attack(Unit*& as);
};

