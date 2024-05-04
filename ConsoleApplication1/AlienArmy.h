#pragma once
#include"Unit.h"

#include"LinkedQueue.h"
#include"DoubleLinkedQueue.h"

#define MAX_LEN 1000
class AlienArmy {
private:
	 LinkedQueue<Unit*> AlienSoldiers;
	DoubleLinkedQueue<Unit*> AlienDrones;
	 Unit* AlienMonsters[MAX_LEN];
	 int id;
	int AScount;
	int ADcount;
	int AMcount;
public:
	AlienArmy();
	void addAlienSoldier(Unit* Soldier);
	void addAlienDrone(Unit* Drone);
	void addAlienDroneFirst(Unit* Drone);
    bool addAlienMonster(Unit* Monster);
	bool RemoveAlienSoldier(Unit*& Soldier);
	bool RemoveAlienDroneFirst(Unit*& Drone);
	bool RemoveAlienDroneLast(Unit*& Drone);
	bool RemoveAlienMonster(Unit*& Monster);
	void printAlienSoldiers();
	void printAlienDrones();
	void printAlienMonsters();
	int  getAScount();
	int  getADcount();
	int  getAMcount();
	void SetAScount(int x);
	void SetADcount(int x);
	void SetAMcount(int x);

	~AlienArmy();
};
