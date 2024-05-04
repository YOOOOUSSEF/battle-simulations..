#pragma once
#include"Unit.h"
#include"AlienDrone.h"
#include"AlienMonster.h"
#include"AlienSoldier.h"
#include"EarthSoldier.h"
#include"EarthTank.h"
#include"Gunnery.h"
class randGen
{
	int A;
	int B;
	Unit* RandUnit;
public:
	randGen();
	bool  GenerateA(int prob);
	int   getRandBetween(int low, int high);
	Unit* GenEarthUnit(int ESpercent, int ETpercent, int EGpercent,int HUpercent, int ESsmall, int EShigh, int ETsmall, int EThigh, int EGsmall, int EGhigh);
	Unit* GenAlienUnit(int ASpercent, int AMpercent, int ADpercent, int ASsmall, int AShigh, int AMsmall, int AMhigh, int ADsmall, int ADhigh);
	
};

