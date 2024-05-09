#include "Game.h"
#include <fstream>
#include<iostream>
using namespace std;
Game::Game()
{
	 timeStep= 0;
	 killedCount = 0;
	//intialize the data members of the game
	cout << "enter the file Name" << endl;
	cin >> fileName;//entering the name of file
	LoadFromFile(fileName);//calling loading file function
	cout << "enter any any Number except -1 to start " << endl;
	
	srand(time(NULL));
	while (timeStep!=50)
	{
		if(R.GenerateA(Prob))//generate randomA from randGen
			for (int i = 0; i < N; i++) 
			{
				Unit* u = R.GenEarthUnit(ES,ET,EG,HU, SmallHealthE, HighHealthE, SmallPowerE, HighPowerE, SmallAttackCapE, HighAttackCapE);//generating an earth unit
				u->setTJ(timeStep);
				if (u->getTYPE() == 0)// if ES
					earthArmy.addEarthSoldier(u);//add to earth soldiers queue
				else if (u->getTYPE() == 1)//if ET
					earthArmy.addEarthTank(u);//add to earth Tanks stack
				else if (u->getTYPE() == 2) earthArmy.addEarthGunnery(u);//add to earth Gunnerys pri queue
				else
					HealList.push(u);                          //add Heal Unit to HealList
			}
		

		if (R.GenerateA(Prob))//generate randomB for randGen
			for (int i = 0; i < N; i++) {
				Unit* u = R.GenAlienUnit(AS,AM , AD, SmallHealthA, HighHealthA, SmallPowerA, HighPowerA, SmallAttackCapA, HighAttackCapA);//generating an alien unit
				u->setTJ(timeStep);
				if (u->getTYPE() == 3)//if AS
					alienArmy.addAlienSoldier(u);//add to alien solders queue
				else if (u->getTYPE() == 4)//if AM
					alienArmy.addAlienMonster(u);//add to alien monsters array of pointers
				else alienArmy.addAlienDrone(u);//add to alien drones doubly linked queue of drones
			}

		
		
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
		
		//cout << "enter any any Number except -1 to conitnue" << endl;
		//cin >> input;
		timeStep++;
		//cout << endl;
	}
	

}


void Game::LoadFromFile(char filename[]) {

	ifstream file; // opening an input file
	string filePath = string(filename) + ".txt"; // concatenate filename with ".txt"
	file.open(filePath.c_str(), ios::in); // open the file with the concatenated file path
	if (!file.is_open()) {
		cerr << "Error opening file: " << filePath << endl;
		return;
	}
	file >> N >> ES >> ET >> EG >>HU>> AS >> AM >> AD >> Prob;//assigning the loading parameters for generation of units
	file >> SmallPowerE >> HighPowerE >> SmallHealthE >>  HighHealthE >> SmallAttackCapE >> HighAttackCapE;//high a low value limits of every type units
	file >> SmallPowerA >> HighPowerA >> SmallHealthA >> HighHealthA >> SmallAttackCapA >> HighAttackCapA;
	HighPowerE = -HighPowerE;//removing the minus sign of the high value
	HighPowerA = -HighPowerA;
	HighHealthE = -HighHealthE;
	HighHealthA = -HighHealthA;
	HighAttackCapA = -HighAttackCapA;
	HighAttackCapE = -HighAttackCapE;
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

/*void Game::TEST()
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


}*/

void Game::AttackLogic() {
	////////////////////////////////////////////////////////////solider
	LinkedQueue<Unit*> TempList;

	Unit* Es = nullptr, * As = nullptr;
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
					TempList.enqueue(As);
				
			}
		}
		earthArmy.addEarthSoldier(Es);
	}
	while (!TempList.isEmpty()) {
		Unit* unit = nullptr;
		TempList.dequeue(unit);
		alienArmy.addAlienSoldier(unit);
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
					TempList.enqueue(Am);
			}
			if (earthArmy.getEScount() < .3 * alienArmy.getAScount()) {
				for (; i < Et->getAttackCap(); ) {
					bool flag1 = false, flag2 = false;
					as = alienArmy.RemoveAlienSoldier(As);
					if (as) {
						i++;
						flag1 = true;
						Et->Attack(As);
						if (As->getTa() == -1)
							As->setTa(timeStep);
						if (As->getHealth() <= 0) {
							As->setTd(timeStep);
							addToKilledList(As);
						}
						else
							TempList.enqueue(As);
					}

					if (earthArmy.getEScount() >= .8 * alienArmy.getAScount())
						break;
					if (i < Et->getAttackCap()) {
						am = alienArmy.RemoveAlienMonster(Am);
						if (am) {
							i++;
							flag2 = true;
							Et->Attack(Am);
							if (Am->getTa() == -1)
								Am->setTa(timeStep);
							if (Am->getHealth() <= 0) {
								Am->setTd(timeStep);
								addToKilledList(Am);
							}
							else
								TempList.enqueue(Am);
						}

					}
					if (!flag1 && !flag2)
						break;

				}
			}
		}
		earthArmy.addEarthTank(Et);
	}
	while (!TempList.isEmpty()) {
		Unit* unit = nullptr;
		TempList.dequeue(unit);
		if (unit->getTYPE() == 3)
			alienArmy.addAlienSoldier(unit);
		else
			alienArmy.addAlienMonster(unit);
	}
	///////////////////////////////////////////////////////////////Gunnery
	Unit* Eg = nullptr, * Adf = nullptr, * Adl = nullptr;
	Am = nullptr;
	bool eg = true, adf = true, adl = true;
	am = true;
	eg = earthArmy.RemoveEarthGunnery(Eg);
	if (eg) {
		for (int i = 0; i < Eg->getAttackCap();) {
			bool flag1 = false, flag2 = false;
			am = alienArmy.RemoveAlienMonster(Am);
			if (am) {
				i++;
				flag1 = true;
				Eg->Attack(Am);
				if (Am->getTa() == -1)
					Am->setTa(timeStep);
				if (Am->getHealth() <= 0) {
					Am->setTd(timeStep);
					addToKilledList(Am);
				}
				else
					TempList.enqueue(Am);
			}

			if (i < Eg->getAttackCap()) {
				adf = alienArmy.RemoveAlienDroneFirst(Adf);
				adl = alienArmy.RemoveAlienDroneLast(Adl);
				if (adl || adf) {
					i++;
					flag2 = true;
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
						TempList.enqueue(Adf);

					if (Adl->getHealth() <= 0) {
						Adl->setTd(timeStep);
						addToKilledList(Adl);
					}
					else
						TempList.enqueue(Adl);
				}
			}
			if (!flag1 && !flag2)
				break;

		}
		earthArmy.addEarthGunnery(Eg);
	}
	while (!TempList.isEmpty()) {
		Unit* unit = nullptr;
		TempList.dequeue(unit);
		if (unit->getTYPE() == 4)
			alienArmy.addAlienMonster(unit);
		else
			alienArmy.addAlienDrone(unit);
	}
	//////////////////////////////////////////////////////////aliensolider
	{

		Unit* Es = nullptr, * As = nullptr;
		bool as = true, es = true;
		as = alienArmy.RemoveAlienSoldier(As);
		if (as)
		{
			for (int i = 0; i < As->getAttackCap(); i++)
			{
				es = earthArmy.RemoveEarthSoldier(Es);
				if (es)
				{
					As->Attack(Es);
					if (Es->getTa() == -1)Es->setTa(timeStep);
					if (Es->getHealth() <= 0)
					{
						if (Es->getTd() == -1)Es->setTd(timeStep);
						addToKilledList(Es);
					}
					else if (Es->getHealth() < .2 * Es->getinitialhealth()) {
						Es->settimeUml(timeStep);
						Uml1.enqueue(Es, 10000 - Es->getHealth());
					}
					else
					{
						TempList.enqueue(Es);
					}
				}
			}
			alienArmy.addAlienSoldier(As);
		}
	}
	while (!TempList.isEmpty()) {
		Unit* unit = nullptr;
		TempList.dequeue(unit);
			earthArmy.addEarthSoldier(unit);
	}
	///////////////////////////////////////////////////////////////////monster
	{

		Unit* Am = nullptr, * Es = nullptr, * Et = nullptr;
		bool am = true, es = true, et = true;

		am = alienArmy.RemoveAlienMonster(Am);
		if (am)
		{
			for (int i = 0; i < Am->getAttackCap(); )
			{
				bool flag1 = false, flag2 = false;
				es = earthArmy.RemoveEarthSoldier(Es);
				if (es) {
					i++;
					flag1 = true;
					Am->Attack(Es);
					if (Es->getTa() == -1)Es->setTa(timeStep);
					if (Es->getHealth() <= 0)
					{
						Es->setTd(timeStep);
						addToKilledList(Es);
					}
					else if (Es->getHealth() < .2 * Es->getinitialhealth()) {
						Es->settimeUml(timeStep);
						Uml1.enqueue(Es, 10000 - Es->getHealth());
					}
					else
					{
						TempList.enqueue(Es);
					}
				}
				if (i < Am->getAttackCap()) {
					et = earthArmy.RemoveEarthTank(Et);
					if (et) {
						i++;
						flag2 = true;
						Am->Attack(Et);
						if (Et->getTa() == -1)Es->setTa(timeStep);
						if (Et->getHealth() <= 0)
						{
							if (Et->getTd() == -1)Et->setTd(timeStep);
							addToKilledList(Et);
						}
						else if (Et->getHealth() < .2 * Et->getinitialhealth()) {
							Et->settimeUml(timeStep);
							Uml2.enqueue(Et);
						}
						else
						{
							TempList.enqueue(Et);
						}
					}
				}

				if (!flag1 && !flag2)
					break;

			}
			alienArmy.addAlienMonster(Am);
		}
	}
	while (!TempList.isEmpty()) {
		Unit* unit = nullptr;
		TempList.dequeue(unit);
		if (unit->getTYPE() == 0)
			earthArmy.addEarthSoldier(unit);
		else
			earthArmy.addEarthTank(unit);
	}

	{
		int capacity;
		///////////////////////////////////////////////////////////////////////////Drones
		Unit* Ad1 = nullptr, * Ad2 = nullptr, * Eg = nullptr, * Et = nullptr;
		bool ad1 = true, ad2 = true, eg = true, et = true;

		ad1 = alienArmy.RemoveAlienDroneFirst(Ad1);
		ad2 = alienArmy.RemoveAlienDroneLast(Ad2);
		if (Ad1->getAttackCap() < Ad2->getAttackCap()) capacity = Ad1->getAttackCap();
		else capacity = Ad2->getAttackCap();
		if (ad1 && ad2)
		{
			for (int i = 0; i < capacity; )
			{
				bool flag1 = false, flag2 = false;
				eg = earthArmy.RemoveEarthSoldier(Eg);

				if (eg) {
					i++;
					flag1 = true;
					Ad1->Attack(Eg);
					Ad2->Attack(Eg);
					if (Eg->getTa() == -1)  Eg->setTa(timeStep);
					if (Eg->getHealth() <= 0)
					{
						if (Eg->getTd() == -1)Eg->setTd(timeStep);
						addToKilledList(Eg);
					}
					else
					{
						TempList.enqueue(Eg);
					}
				}
				if (i < capacity) {
					et = earthArmy.RemoveEarthTank(Et);
					if (et) {
						i++;
						flag2 = true;
						Ad1->Attack(Et);
						Ad2->Attack(Et);
						if (Et->getTa() == -1)Et->setTa(timeStep);
						if (Et->getHealth() <= 0)
						{
							if (Et->getTd() == -1)Et->setTd(timeStep);
							addToKilledList(Et);
						}
						else if (Et->getHealth() < .2 * Et->getinitialhealth()) {
							Et->settimeUml(timeStep);
							Uml2.enqueue(Et);
						}
						else
						{
							TempList.enqueue(Et);
						}
					}
				}
				if (!flag1 && !flag2)
					break;

			}
			alienArmy.addAlienDroneFirst(Ad1);
			alienArmy.addAlienDrone(Ad2);
		}
	}
	while (!TempList.isEmpty()) {
		Unit* unit = nullptr;
		TempList.dequeue(unit);
		if (unit->getTYPE() == 1)
			earthArmy.addEarthTank(unit);
		else
			earthArmy.addEarthGunnery(unit);
	}
}

void Game::HealLogic() {
	LinkedQueue<Unit*>TempListforsoilder;
	LinkedQueue<Unit*>TempListfortank;
	int f;
	Unit* healunit = nullptr,*healed=nullptr;

	if (HealList.pop(healunit)) 
		for (int i = 0; i < healunit->getAttackCap(); i++) {
			if (Uml1.dequeue(healed, f)) {
				if (timeStep - healed->gettimeUml() > 10) {
					addToKilledList(healed);
					i--;
					continue;
				}
				healunit->Attack(healed);
				if (healed->getHealth() > .2 * healed->getinitialhealth()) {
					earthArmy.addEarthSoldier(healed);
					healed->settimeUml(-1);
				}
				else {
					TempListforsoilder.enqueue(healed);
					healed->settimeUml(timeStep);
				}

			}
			else if (Uml2.dequeue(healed)) {
				if (timeStep - healed->gettimeUml() > 10) {
					addToKilledList(healed);
					i--;
					continue;
				}
				healunit->Attack(healed);
				if (healed->getHealth() > .2 * healed->getinitialhealth()) {
					earthArmy.addEarthTank(healed);
					healed->settimeUml(-1);
				}
				else {
					TempListfortank.enqueue(healed);
					healed->settimeUml(timeStep);
				}
			}
			else
				break;
		}
	Unit* deleter = nullptr;
	while (TempListfortank.dequeue(deleter)) 
		Uml2.enqueue(deleter);
	
	while (TempListforsoilder.dequeue(deleter))
		Uml1.enqueue(deleter, 10000 - deleter->getHealth());
	
}