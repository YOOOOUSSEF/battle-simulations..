#pragma once

#include"LinkedQueue.h""
#include"priQueue.h"
#include"Unit.h"
#include"ArrayStack.h"
class EarthArmy {
private:
	LinkedQueue<Unit*> EarthSoldiers;
	priQueue<Unit*> EarthGunnerys;
	ArrayStack<Unit*> EarthTanks;
	ArrayStack<Unit*>HealList;

	int EScount;
	int EGcount;
	int ETcount;
	int HUcount;
	int id;
public:
	EarthArmy();
	void addEarthSoldier(Unit* soldier);
	void addEarthGunnery(Unit* Gunnery);
	void addEarthTank(Unit* EarthTank);
	void addHealUnit(Unit* HealUnit);
	bool RemoveEarthSoldier(Unit*& EarthSoldier);
	bool RemoveEarthGunnery(Unit*& EarthGunnery);
	bool RemoveEarthTank(Unit*& EarthTank);
	bool RemoveHealUnit(Unit*& HealUnit);
	void printEarthSoldiers();
	void printEarthTanks();
	void printEarthGunnerys();
	void printHealUnits();
	int  getEScount();
	int  getETcount();
	int  getEGcount();

	void SetEScount(int x);

	void SetETcount(int x);

	void SetEGcount(int x);

	~EarthArmy();
};
