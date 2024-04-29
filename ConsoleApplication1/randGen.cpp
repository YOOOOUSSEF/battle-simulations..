#include "randGen.h"
#include "cstdlib"
randGen::randGen()
{
	A = 0;
}

bool randGen::GenerateA(int prob)
{
	A = rand() % 100 + 1;//generate random number from 1 to 100
	if (A <= prob)
		return true;
	else return false;
}

int randGen::getRandBetween(int low, int high)
{
	return rand()%(high - low +1)+low;
}

Unit* randGen::GenEarthUnit(int ESpercent, int ETpercent, int EGpercent, int ESsmall, int EShigh, int ETsmall, int EThigh, int EGsmall ,int EGhigh)
{


	B = rand() % 100 + 1;//generate random number from 1 to 100
	if (B <= ESpercent)//we are in ES region
	{        
		RandUnit = new EarthSoldier();//generate a new earth Soldier
		RandUnit->settype(0);//set its type to ES
		//then generating random power , health and ATCapcity//
		int tempPower = getRandBetween(ESsmall,EShigh);
		RandUnit->setPower(tempPower);
		int tempHealth = getRandBetween(ESsmall, EShigh);
		RandUnit->setHealth(tempHealth);
		int tempATCap = getRandBetween(ESsmall, EShigh);
		RandUnit->setAttackCap(tempATCap);
		///////////////////
		return RandUnit;
	}
	else if (B <= ESpercent + ETpercent)
	{
		RandUnit = new EarthTank();//generate a new earth tank
		RandUnit->settype(1);//set its type to ET
		//then generating random power , health and ATCapcity//
		int tempPower = getRandBetween(ETsmall, EThigh);
		RandUnit->setPower(tempPower);
		int tempHealth = getRandBetween(ETsmall, EThigh);
		RandUnit->setHealth(tempHealth);
		int tempATCap = getRandBetween(ETsmall, EThigh);
		RandUnit->setAttackCap(tempATCap);
		return RandUnit;
	}

	else
	{
		RandUnit = new Gunnery();//generte a gunnery
		RandUnit->settype(2);//set its type to EarthGunnery
		//then generating random power , health and ATCapcity//
		int tempPower = getRandBetween(EGsmall, EGhigh);
		RandUnit->setPower(tempPower);
		int tempHealth = getRandBetween(EGsmall, EGhigh);
		RandUnit->setHealth(tempHealth);
		int tempATCap = getRandBetween(EGsmall, EGhigh);
		RandUnit->setAttackCap(tempATCap);
		return RandUnit;
	}
}

Unit* randGen::GenAlienUnit(int ASpercent, int AMpercent, int ADpercent, int ASsmall, int AShigh, int AMsmall, int AMhigh, int ADsmall, int ADhigh)
{

	B = rand() % 100 + 1;//generate random number from 1 to 100
	if (B <= ASpercent)
	{
		RandUnit = new AlienSoldier();//generate a new alien soldier
		//set type to alien Soldier
		RandUnit->settype(3);//
		//then generating random power , health and ATCapcity//
		int tempPower = getRandBetween(ASsmall, AShigh);
		RandUnit->setPower(tempPower);
		int tempHealth = getRandBetween(ASsmall, AShigh);
		RandUnit->setHealth(tempHealth);
		int tempATCap = getRandBetween(ASsmall, AShigh);
		RandUnit->setAttackCap(tempATCap);
		return RandUnit;
	}
	else if (B <= ASpercent + AMpercent)
	{
		RandUnit = new AlienMonster();
		RandUnit->settype(4);//set type to alien monster
		//then generating random power , health and ATCapcity//
		int tempPower = getRandBetween(AMsmall, AMhigh);
		RandUnit->setPower(tempPower);
		int tempHealth = getRandBetween(AMsmall, AMhigh);
		RandUnit->setHealth(tempHealth);
		int tempATCap = getRandBetween(AMsmall, AMhigh);
		RandUnit->setAttackCap(tempATCap);
		return RandUnit;
	}

	else
	{
		RandUnit = new AlienDrone();//generate a new alien drone
		RandUnit->settype(5);//set type to AD
		//then generating random power , health and ATCapcity//
		int tempPower = getRandBetween(ADsmall, ADhigh);
		RandUnit->setPower(tempPower);
		int tempHealth = getRandBetween(ADsmall, ADhigh);
		RandUnit->setHealth(tempHealth);
		int tempATCap = getRandBetween(ADsmall, ADhigh);
		RandUnit->setAttackCap(tempATCap);
		return RandUnit;
	}
}

