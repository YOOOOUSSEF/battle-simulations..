#pragma once
#include"AlienArmy.h"
#include"EarthArmy.h"
#include"randGen.h"
#include"LinkedQueue.h"
#include"HEAL.h"
class Game
{
private:
	int N, ES, ET,EG,HU, AS, AM, AD, Prob;
	int SmallPowerE, HighPowerE;
	int SmallHealthE, HighHealthE;
	int SmallAttackCapE, HighAttackCapE;
	int SmallPowerA, HighPowerA;
	int SmallHealthA, HighHealthA;
	int SmallAttackCapA, HighAttackCapA;
	EarthArmy earthArmy;
	AlienArmy alienArmy;
	randGen R;
	
	LinkedQueue<Unit*> KilledList;
	ArrayStack<Unit*>HealList;
	priQueue<Unit*>Uml1; //for earth soilder
	LinkedQueue<Unit*>Uml2; //for earth tank
	int killedCount,timeStep;
	char fileName[100];
public:
	Game();
	void AttackLogic();
	void HealLogic();
	void LoadFromFile(char filename[]);
	void addToKilledList(Unit* killed);
	void PrintKilledList() const; 
	//void TEST();
	

};

