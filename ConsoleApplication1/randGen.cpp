#include "randGen.h"
#include "cstdlib"
#include"HEAL.h"
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

Unit* randGen::GenEarthUnit(int ESpercent, int ETpercent, int EGpercent,int HUpercent, int smallHealth, int highHealth, int smallPower, int highPower, int smallAttackCap ,int highAttackCap)
{


	B = rand() % 100 + 1;//generate random number from 1 to 100
	if (B <= ESpercent)//we are in ES region
	{        
		RandUnit = new EarthSoldier();//generate a new earth Soldier
		RandUnit->settype(0);//set its type to ES
		//then generating random power , health and ATCapcity//
		int tempPower = getRandBetween(smallPower,highPower);
		RandUnit->setPower(tempPower);
		int tempHealth = getRandBetween(smallHealth, highHealth);
		RandUnit->setHealth(tempHealth);
		RandUnit->setinitialhealth(tempHealth);
		int tempATCap = getRandBetween(smallAttackCap, highAttackCap);
		RandUnit->setAttackCap(tempATCap);
		///////////////////
		return RandUnit;
	}
	else if (B <= ESpercent + ETpercent)
	{
		RandUnit = new EarthTank();//generate a new earth tank
		RandUnit->settype(1);//set its type to ET
		//then generating random power , health and ATCapcity//
		int tempPower = getRandBetween(smallPower, highPower);
		RandUnit->setPower(tempPower);
		int tempHealth = getRandBetween(smallHealth, highHealth);
		RandUnit->setHealth(tempHealth);
		RandUnit->setinitialhealth(tempHealth);
		int tempATCap = getRandBetween(smallAttackCap, highAttackCap);
		RandUnit->setAttackCap(tempATCap);
		return RandUnit;
	}

	else if(B<= ESpercent + ETpercent+EGpercent)
	{
		RandUnit = new Gunnery();//generate a new earth Gunnery
		RandUnit->settype(1);//set its type to ET
		//then generating random power , health and ATCapcity//
		int tempPower = getRandBetween(smallPower, highPower);
		RandUnit->setPower(tempPower);
		int tempHealth = getRandBetween(smallHealth, highHealth);
		RandUnit->setHealth(tempHealth);
		int tempATCap = getRandBetween(smallAttackCap, highAttackCap);
		RandUnit->setAttackCap(tempATCap);
		return RandUnit;
	}
	else {
		RandUnit = new HEAL();//generte a HEAL Unit
		RandUnit->settype(6);//set its type to EarthGunnery
		//then generating random power , health and ATCapcity//
		int tempPower = getRandBetween(smallPower, highPower);
		RandUnit->setPower(tempPower);
		int tempHealth = getRandBetween(smallHealth, highHealth);
		RandUnit->setHealth(tempHealth);
		int tempATCap = getRandBetween(smallAttackCap, highAttackCap);
		RandUnit->setAttackCap(tempATCap);
		return RandUnit;
	}
}

Unit* randGen::GenAlienUnit(int ASpercent, int AMpercent, int ADpercent, int smallHealth, int highHealth, int smallPower, int highPower, int smallAttackCap, int highAttackCap)
{

	B = rand() % 100 + 1;//generate random number from 1 to 100
	if (B <= ASpercent)
	{
		RandUnit = new AlienSoldier();//generate a new alien soldier
		//set type to alien Soldier
		RandUnit->settype(3);//
		//then generating random power , health and ATCapcity//
		int tempPower = getRandBetween(smallPower, highPower);
		RandUnit->setPower(tempPower);
		int tempHealth = getRandBetween(smallHealth, highHealth);
		RandUnit->setHealth(tempHealth);
		int tempATCap = getRandBetween(smallAttackCap, highAttackCap);
		RandUnit->setAttackCap(tempATCap);
		return RandUnit;
	}
	else if (B <= ASpercent + AMpercent)
	{
		RandUnit = new AlienMonster();
		RandUnit->settype(4);//set type to alien monster
		//then generating random power , health and ATCapcity//
		int tempPower = getRandBetween(smallPower, highPower);
		RandUnit->setPower(tempPower);
		int tempHealth = getRandBetween(smallHealth, highHealth);
		RandUnit->setHealth(tempHealth);
		int tempATCap = getRandBetween(smallAttackCap, highAttackCap);
		RandUnit->setAttackCap(tempATCap);
		return RandUnit;;
	}

	else
	{
		RandUnit = new AlienDrone();//generate a new alien drone
		RandUnit->settype(5);//set type to AD
		//then generating random power , health and ATCapcity//
		int tempPower = getRandBetween(smallPower, highPower);
		RandUnit->setPower(tempPower);
		int tempHealth = getRandBetween(smallHealth, highHealth);
		RandUnit->setHealth(tempHealth);
		int tempATCap = getRandBetween(smallAttackCap, highAttackCap);
		RandUnit->setAttackCap(tempATCap);
		return RandUnit;
	}
}

