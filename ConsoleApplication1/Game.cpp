#include "Game.h"
#include <fstream>
#include<iostream>
using namespace std;
Game::Game()
{
	int input;
	 timeStep = 0;
	 killedCount = 0;
	//intialize the data members of the game
	cout << "enter the file Name" << endl;
	cin >> fileName;//entering the name of file
	LoadFromFile(fileName);//calling loading file function
	cout << "enter any any Number except -1 to start " << endl;
	cin >> input;//while(the input is not -1) the function will continue
	srand(time(NULL));
	while (input != -1||timeStep==50)
	{
		if(R.GenerateA(Prob))//generate randomA from randGen
			for (int i = 0; i < N; i++) 
			{
				Unit* u = R.GenEarthUnit(ES,ET,EG,SmallPowerES,HighPowerES,SmallPowerET,HighPowerET,SmallPowerEG,HighPowerEG);//generating an earth unit
				u->setTJ(timeStep);
				if (u->getTYPE() == 0)// if ES
					earthArmy.addEarthSoldier(u);//add to earth soldiers queue
				else if (u->getTYPE() == 1)//if ET
					earthArmy.addEarthTank(u);//add to earth Tanks stack
				else earthArmy.addEarthGunnery(u);//add to earth Gunnerys pri queue
			}
		

		if (R.GenerateA(Prob))//generate randomB for randGen
			for (int i = 0; i < N; i++) {
				Unit* u = R.GenAlienUnit(AS,AM , AD, SmallPowerAS, HighPowerAS, SmallPowerAM, HighPowerAM, SmallPowerAD, HighPowerAD);//generating an alien unit
				u->setTJ(timeStep);
				if (u->getTYPE() == 3)//if AS
					alienArmy.addAlienSoldier(u);//add to alien solders queue
				else if (u->getTYPE() == 4)//if AM
					alienArmy.addAlienMonster(u);//add to alien monsters array of pointers
				else alienArmy.addAlienDrone(u);//add to alien drones doubly linked queue of drones
			}

		TEST();//calling the testing fuction
		cout << "Current Timestep " << timeStep << endl;//cout current time Step
		cout << "============== Earth Army Alive Units ============== " << endl;//printing earth army lists
        earthArmy.printEarthSoldiers();
		earthArmy.printEarthTanks();
		earthArmy.printEarthGunnerys();
		cout << "============== Alien Army Alive Units ============== " << endl;//printing alien army lists
		alienArmy.printAlienSoldiers();
		alienArmy.printAlienDrones();
		alienArmy.printAlienMonsters();
		cout << "============== Killed/Destructed Units ============= " << endl;
		PrintKilledList();//printing the killed list of units

		cout << "enter any any Number except -1 to conitnue" << endl;
		cin >> input;
		timeStep++;
		cout << endl;
	}

}
void Game::LoadFromFile(char filename[]) {
	ifstream file;//opening a input file
	file.open(filename, ios::in);
		file >> N >> ES >> ET >> EG >> AS >> AM >> AD >> Prob;//assigning the loading parameters for generation of units
		file >> SmallPowerES >> HighPowerES >> SmallPowerET >>  HighPowerET >> SmallPowerEG >> HighPowerEG;//high a low value limits of every type units
		file >> SmallPowerAS >> HighPowerAS >> SmallPowerAM >>  HighPowerAM >> SmallPowerAD >> HighPowerAD;
		HighPowerES = -HighPowerES;//removing the minus sign of the high value
		HighPowerET = -HighPowerET;
		HighPowerEG = -HighPowerEG;
		HighPowerAS = -HighPowerAS;
		HighPowerAM = -HighPowerAM;
		HighPowerAD = -HighPowerAD;
		file.close();
	
}

void Game::addToKilledList(Unit* killed)
{
	KilledList.enqueue(killed);
	killedCount++;
}

void Game::PrintKilledList() const
{
	cout << killedCount << " Units [";
	KilledList.print_the_list();
	cout << "] ";
	cout << endl;
}

void Game::TEST()
{
	
	int X = rand()%100+1;//rand x from 1 to 100
	Unit* temp= NULL;
	Unit* temp2 = NULL;
	if (X < 10)
	{
		earthArmy.RemoveEarthSoldier(temp);//dequeue from earth soldiers queue 
		if(temp)//checking if not equal null
		earthArmy.addEarthSoldier(temp);//back it to its list
	}

	else if (X<20)
	{
		earthArmy.RemoveEarthTank(temp);//pop from earth tank Stack
		if(temp)//if there is top
		addToKilledList(temp);//adding it to killed list
	}

	else if (X < 30)
	{
		earthArmy.RemoveEarthGunnery(temp);//dequeuing an earth Gunnery
		if (temp)//if exsits
		{
			temp->setHealth(temp->getHealth() / 2);//decrement its health to its half
			earthArmy.addEarthGunnery(temp);//back it to its list
		}
	}

	else if (X < 40)
	{
		if (alienArmy.getAScount() >= 5)
		{

			for (int i = 0; i < 5; i++)//if we have 5 AS or more dequeue 5 AS
			{
				alienArmy.RemoveAlienSoldier(temp);//dequeuing an alienSoldier
				if (temp) {
					temp->setHealth(temp->getHealth() / 2);//decrement its health
					TempList.enqueue(temp);  //go to templist
				}
			}

			for (int i = 0; i < 5; i++)
			{
				TempList.dequeue(temp);//dequeuing from templist
				if(temp)
				alienArmy.addAlienSoldier(temp);//back it its original list
			}
		}

		else {
			for (int i = 0; i < alienArmy.getAScount(); i++)//same logic but with less number of AS
			{
				alienArmy.RemoveAlienSoldier(temp);
				if (temp) {
					temp->setHealth(temp->getHealth() / 2);
					TempList.enqueue(temp);
				}
			}

			for (int i = 0; i < alienArmy.getAScount(); i++)
			{
				TempList.dequeue(temp);
				if(temp)
				alienArmy.addAlienSoldier(temp);
			}

		}
	}
	else if (X < 50)
	{
		if(alienArmy.getAMcount()>=5)//if we have 5 AM or more
			for (int i = 0; i < 5; i++)//take 5 AMs
			{
				alienArmy.RemoveAlienMonster(temp);//remove them from the array randomly
				if(temp)
				alienArmy.addAlienMonster(temp);//back it  to the array
			}
		else 
			for (int i = 0; i < alienArmy.getAMcount() ;i++)//same logic if we have less number
			{
				alienArmy.RemoveAlienMonster(temp);
				if(temp)
				alienArmy.addAlienMonster(temp);
			}
	}
	
	else if (X < 60)
	{
		if (alienArmy.getADcount() >= 6)//if we have 6AS or more
		{
			for(int i=0;i<3;i++)//dequeuing 6 ADs from first and last
			{
				alienArmy.RemoveAlienDroneFirst(temp);
				alienArmy.RemoveAlienDroneLast(temp2);
				if(temp)addToKilledList(temp);//back them to killed list
				if(temp2)addToKilledList(temp2);//back them to killed list
			}
		}
		else 
		{
         
			while(alienArmy.getADcount()!=0)//if we have a number less than 6
			{//same logic
				alienArmy.RemoveAlienDroneFirst(temp);
				alienArmy.RemoveAlienDroneLast(temp2);

			  	if(temp)addToKilledList(temp);
			    if(temp2)addToKilledList(temp2);

		    }

		}

	}


}

void Game::AttackLogic() {
	////////////////////////////////////////////////////////////solider
	Unit* Es = nullptr,*As=nullptr;
	bool as = true, es = true;
	es = earthArmy.RemoveEarthSoldier(Es);
	if (es) {
		for (int i = 0; i < Es->getAttackCap(); i++) {
			as = alienArmy.RemoveAlienSoldier(As);
			if (as) {
				Es->Attack(As);
				if (As->getTa() == -1)
					As->setTa(timeStep);
				if (As->getHealth() <= 0) {
					As->setTd(timeStep);
					addToKilledList(As);
				}
				else
					alienArmy.addAlienSoldier(As);
			}
		}
		earthArmy.addEarthSoldier(Es);
	}
	//////////////////////////////////////////////////////////tank
	Unit* Et = nullptr, * Am = nullptr;
	As = nullptr;
	bool et = true, am = true;
	et = earthArmy.RemoveEarthTank(Et);
	if (et) {
		for (int i = 0; i < Et->getAttackCap(); i++) {
			am = alienArmy.RemoveAlienMonster(Am);
			if (am) {
				Et->Attack(Am);
				if (Am->getTa() == -1)
					Am->setTa(timeStep);
				if (Am->getHealth() <= 0) {
					Am->setTd(timeStep);
					addToKilledList(Am);
				}
				else
					alienArmy.addAlienMonster(Am);
			}
			if (earthArmy.getEScount() < .3 * alienArmy.getAScount()) {
				for (; i < Et->getAttackCap(); i++) {
					as = alienArmy.RemoveAlienSoldier(As);
					if (as) {
						Et->Attack(As);
						if (As->getTa() == -1)
							As->setTa(timeStep);
						if (As->getHealth() <= 0) {
							As->setTd(timeStep);
							addToKilledList(As);
						}
						else
							alienArmy.addAlienSoldier(As);
					}
					if (earthArmy.getEScount() >= .8 * alienArmy.getAScount())
						break;
					am = alienArmy.RemoveAlienMonster(Am);
					if (am) {
						i++;
						Et->Attack(Am);
						if (Am->getTa() == -1)
							Am->setTa(timeStep);
						if (Am->getHealth() <= 0) {
							Am->setTd(timeStep);
							addToKilledList(Am);
						}
						else
							alienArmy.addAlienMonster(Am);
					}

				}
			}
		}
		earthArmy.addEarthTank(Es);
	}
	///////////////////////////////////////////////////////////////Gunnery
	Unit* Eg = nullptr, * Adf = nullptr,*Adl=nullptr;
	Am = nullptr;
	bool eg = true, adf = true,adl=true;
	am = true;
	eg = earthArmy.RemoveEarthGunnery(Eg);
	if (eg) {
		for (int i = 0; i < Eg->getAttackCap(); i++) {
			am = alienArmy.RemoveAlienMonster(Am);
			if (am) {
				Eg->Attack(Am);
				if (Am->getTa() == -1)
					Am->setTa(timeStep);
				if (Am->getHealth() <= 0) {
					Am->setTd(timeStep);
					addToKilledList(Am);
				}
				else
					alienArmy.addAlienMonster(Am);
			}
			adf = alienArmy.RemoveAlienDroneFirst(Adf);
			adl = alienArmy.RemoveAlienDroneLast(Adl);
			if (adl && adf) {
				i++;
				Eg->Attack(Adf);
				Eg->Attack(Adl);
				if (Adf->getTa() == -1)
					Adf->setTa(timeStep);
				if (Adl->getTa() == -1)
					Adl->setTa(timeStep);
				if (Adf->getHealth() <= 0) {
					Adf->setTd(timeStep);
					addToKilledList(Adf);
				}
				else
					alienArmy.addAlienDrone(Adf);

				if (Adl->getHealth() <= 0) {
					Adl->setTd(timeStep);
					addToKilledList(Adl);
				}
				else
					alienArmy.addAlienDrone(Adl);
			}

		}
		earthArmy.addEarthGunnery(Eg);
	}
	//////////////////////////////////////////////////////////

}