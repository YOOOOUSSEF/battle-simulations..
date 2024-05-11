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

	int EScount;
	int EGcount;
	int ETcount;
	int id;
public:
	EarthArmy();
	void addEarthSoldier(Unit* soldier);
	void addEarthGunnery(Unit* Gunnery);
	void addEarthTank(Unit* EarthTank);
	bool RemoveEarthSoldier(Unit*& EarthSoldier);
	bool RemoveEarthGunnery(Unit*& EarthGunnery);
	bool RemoveEarthTank(Unit*& EarthTank);
	void printEarthSoldiers();
	void printEarthTanks();
	void printEarthGunnerys();
	int  getEScount();
	int  getETcount();
	int  getEGcount();

	void SetEScount(int x);

	void SetETcount(int x);

	void SetEGcount(int x);

	~EarthArmy();
};
