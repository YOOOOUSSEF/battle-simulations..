#pragma once
#include"AlienArmy.h"
#include"EarthArmy.h"
#include"randGen.h"
#include"LinkedQueue.h"
class Game
{
private:
	int N, ES, ET,EG, AS, AM, AD, Prob;
	int SmallPowerES, HighPowerES;
	int SmallPowerET, HighPowerET;
	int SmallPowerEG, HighPowerEG;
	int SmallPowerAS, HighPowerAS;
	int SmallPowerAM, HighPowerAM;
	int SmallPowerAD, HighPowerAD;
	EarthArmy earthArmy;
	AlienArmy alienArmy;
	randGen R;
	LinkedQueue<Unit*> TempList;
	LinkedQueue<Unit*> KilledList;
	int killedCount,timeStep;
	char fileName[100];
public:
	Game();
	void AttackLogic();
	void LoadFromFile(char filename[]);
	void addToKilledList(Unit* killed);
	void PrintKilledList() const; 
	void TEST();
	

};

