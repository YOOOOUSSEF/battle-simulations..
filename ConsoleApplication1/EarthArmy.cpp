#include "EarthArmy.h"

EarthArmy::EarthArmy()
{
	id = 1;
	EScount = 0;
	EGcount = 0;
	ETcount = 0;
	HUcount = 0;
}

void EarthArmy::addEarthSoldier(Unit* soldier)
{
	EarthSoldiers.enqueue(soldier); // calling the enqueue function of the queue of aliensoliders
	if (soldier->getID() == -1)
	{
		soldier->setID(id);
		id++;
	}
	EScount++;
}

void EarthArmy::addEarthGunnery(Unit* Gunnery)
{
	EarthGunnerys.enqueue(Gunnery,Gunnery->getHealth()*Gunnery->getPower()); // calling the enqueue function of the queue of aliensoliders
	//and making the prioirty the multiplication of the health and the power
	if (Gunnery->getID() == -1)//checking that we have a new Unit
	{
		Gunnery->setID(id);
		id++;
	}
	EGcount++;
}

void EarthArmy::addEarthTank(Unit* EarthTank)
{
	EarthTanks.push(EarthTank);//pushing to EarthTanks Stack
	if (EarthTank->getID()==-1)//check that we have a new Unit
	{
		EarthTank->setID(id);
		id++;
	}
	ETcount++;
}
void EarthArmy::addHealUnit(Unit* HealUnit) {
	HealList.push(HealUnit);//pushing to HealList Stack
	if (HealUnit->getID() == -1)//check that we have a new Unit
	{
		HealUnit->setID(id);
		id++;
	}
	HUcount++;
}

bool EarthArmy::RemoveEarthSoldier(Unit*& EarthSoldier)
{
	if (EScount == 0)
	{
		EarthSoldier = NULL;
		return false;
	}
	EarthSoldiers.dequeue(EarthSoldier);//dequeuing the earthSoldiers 
	EScount--;
	return true;
}

bool EarthArmy::RemoveEarthGunnery(Unit*& EarthGunnery)
{
	if (EGcount == 0)
	{
		EarthGunnery = NULL;
		return false;
	}
	int x = 0;
	EarthGunnerys.dequeue(EarthGunnery, x);//dequeuing the earthGunnerys
	EGcount--;
	return true;
}

bool EarthArmy::RemoveEarthTank(Unit*& EarthTank)
{
	if (EarthTanks.isEmpty())
	{
		EarthTank = NULL;
		return false;
	}

	EarthTanks.pop(EarthTank);//poping the earthTanks
	ETcount--;
	return true;
}
bool EarthArmy::RemoveHealUnit(Unit*& HealUnit) {
	if (HealList.isEmpty()) {
		HealUnit = nullptr;
		return false;
	}
	HealList.pop(HealUnit);
	HUcount--;
	return true;
}

void EarthArmy::printEarthSoldiers()
{
	cout << EScount << " ES [";
	EarthSoldiers.print_the_list();
	cout << "] ";
	cout << endl;
}

void EarthArmy::printEarthTanks()
{
	cout << ETcount << " ET [";
	EarthTanks.print_list();
	cout << "] ";
	cout << endl;
}

void EarthArmy::printEarthGunnerys()
{
	cout << EGcount << " EG [";
	EarthGunnerys.print_the_list();
	cout << "] ";
	cout << endl;
}

void EarthArmy::printHealUnits() {
	cout << HUcount << " HU [";
	HealList.print_list();
	cout << "]" << endl;
}

int EarthArmy::getEScount()
{
	return EScount;
}

int EarthArmy::getETcount()
{
	return ETcount;
}

int EarthArmy::getEGcount()
{
	return EGcount;
}

void EarthArmy::SetEScount(int x)
{
	EScount = x;
}

void EarthArmy::SetETcount(int x)
{
	ETcount = x;
}

void EarthArmy::SetEGcount(int x)
{
	
	EGcount = x;
}

EarthArmy::~EarthArmy()
{
	Unit* Delete;
	int x;
	while (!EarthSoldiers.isEmpty())
	{
		EarthSoldiers.dequeue(Delete);
		delete Delete;
	}

	while (!EarthGunnerys.isEmpty())
	{
		EarthGunnerys.dequeue(Delete,x);
		delete Delete;
	}

	while (!EarthTanks.isEmpty())
	{
		EarthTanks.pop(Delete);
		delete Delete;
	}

	id = 1;
	EScount = 0;
	EGcount = 0;
	ETcount = 0;
}

