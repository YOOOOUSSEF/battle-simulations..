#include "Game.h"
#include <fstream>
#include<iostream>
using namespace std;
Game::Game()
{
	int input;
	int timeStep = 0;
	int killedCount = 0;
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
