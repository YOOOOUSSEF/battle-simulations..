#include "Game.h"
#include <fstream>
#include<iostream>
#include<string.h>
using namespace std;
Game::Game()
{
	int input;
	num_of_healed = 0;
	counterForUML1 = counterForUML2 = 0;
	 timeStep= 0;
	 killedCount = 0;
	 killedcountEs = killedcountEt = killedcountEg = killedcountAs = killedcountAm = killedcountAd = 0;
	//intialize the data members of the game
	cout << "enter the file Name" << endl;
	cin >> fileName;//entering the name of file
	LoadFromFile(fileName);//calling loading file function
	cout << "enter any any Number except -1 to start " << endl;
	
	
	cin >> input;
	srand(time(NULL));
	while (input!=-1||timeStep!=50)
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
				else {
					earthArmy.addHealUnit(u);
				}                          //add Heal Unit to HealList
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

		AttackLogic();
	
		cout << "if you want to terminate the program press -1"<<endl;
		cin >> input;

		timeStep++;
	
	}
	

}


void Game::LoadFromFile(char filename[]) {

	char filePath[100];
	ifstream file; // opening an input file
	for (int i = 0; i < strlen(filename); i++)
		filePath[i] = filename[i];
	filePath[strlen(filename)] = '.';
	filePath[strlen(filename)+1] = 't';
	filePath[strlen(filename)+2] = 'x';
	filePath[strlen(filename)+3] = 't';
	filePath[strlen(filename)+4] = '\0';

	file.open(filePath, ios::in); // open the file with the concatenated file path
	if (!file.is_open()) {
		cerr << "Error opening file: " << filename << endl;
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
if(killed->getTYPE()==0)
	killedcountEs++;
if (killed->getTYPE() == 1)
	killedcountEt++;
if (killed->getTYPE() == 2)
	killedcountEg++;
if (killed->getTYPE() == 3)
	killedcountAs++;
if (killed->getTYPE() == 4)
	killedcountAm++;
if (killed->getTYPE() == 5)
	killedcountAd++;
}

void Game::PrintKilledList() const
{
	cout << killedCount << " Units [";
	KilledList.print_the_list();
	cout << "] ";
	cout << endl;
}







void Game::AttackLogic() {
	////////////////////////////////////////////////////////////solider
	LinkedQueue<Unit*> TempList;
	LinkedQueue<Unit*> AttackedFromES;
	LinkedQueue<Unit*> AttackedFromETforMonster;
	LinkedQueue<Unit*> AttackedFromETforSoilder;
	LinkedQueue<Unit*> AttackedFromEGforMonster;
	LinkedQueue<Unit*> AttackedFromEGforDrones;
	LinkedQueue<Unit*> AttackedFromAS;
	LinkedQueue<Unit*> AttackedFromAMforSoilder;
	LinkedQueue<Unit*> AttackedFromAMforTank;
	LinkedQueue<Unit*> AttackedFromADforGunnery;
	LinkedQueue<Unit*> AttackedFromADforTank;


	Unit* Es = nullptr, * As = nullptr;
	bool as = true, es = true;
	es = earthArmy.RemoveEarthSoldier(Es);
	if (es) {
		if (timeStep == 49)
		AttackedFromES.enqueue(Es);//the attacker unit
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
				if (timeStep == 49)
				AttackedFromES.enqueue(As);//List for printing the last attacked As
				
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
		if (timeStep == 49)
		AttackedFromETforMonster.enqueue(Et);//the Attacker unit
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
				if (timeStep == 49)
				AttackedFromETforMonster.enqueue(Am);//List for printing the last attacked Am by ET
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
						if (timeStep == 49)
						AttackedFromETforSoilder.enqueue(As);//List for printing the last attacked As
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
							if (timeStep == 49)
							AttackedFromETforMonster.enqueue(Am);//List for printing the last attacked Am by ET
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
		if (timeStep == 49)
		AttackedFromEGforMonster.enqueue(Eg);//the Attacker unit
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
				if (timeStep == 49)
				AttackedFromEGforMonster.enqueue(Am);//List for printing the last attacked Am by EG
			}

			if (i < Eg->getAttackCap()) {
				adf = alienArmy.RemoveAlienDroneFirst(Adf);
				adl = alienArmy.RemoveAlienDroneLast(Adl);
				if (adl || adf) {
					i++;
					flag2 = true;
					if (adl) {
						Eg->Attack(Adl);
						if (Adl->getTa() == -1)
							Adl->setTa(timeStep);
						if (Adl->getHealth() <= 0) {
							Adl->setTd(timeStep);
							addToKilledList(Adl);
						}
						else
							TempList.enqueue(Adl);
						if (timeStep == 49)
						AttackedFromEGforDrones.dequeue(Adl);//List for printing the last attacked AD
					}
					if (adf) {
						Eg->Attack(Adf);

						if (Adf->getTa() == -1)
							Adf->setTa(timeStep);

						if (Adf->getHealth() <= 0) {
							Adf->setTd(timeStep);
							addToKilledList(Adf);
						}
						else
							TempList.enqueue(Adf);
						if (timeStep == 49)
						AttackedFromEGforDrones.dequeue(Adf);//List for printing the last attacked AD
					}
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
			if (timeStep == 49)
				AttackedFromAS.enqueue(As);//the Attacker unit
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
						counterForUML1++;
					}
					else
					{
						TempList.enqueue(Es);
					}
					if (timeStep == 49)
						AttackedFromAS.enqueue(Es);//List for printing the last attacked ES by AS
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
			if (timeStep == 49)
			AttackedFromAMforSoilder.enqueue(Am);//the Attacker unit

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
						counterForUML1++;
					}
					else
					{
						TempList.enqueue(Es);
					}
					if (timeStep == 49)
						AttackedFromAMforSoilder.enqueue(Es);//List for printing the last attacked ES by AM
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
							counterForUML2++;
						}
						else
						{
							TempList.enqueue(Et);
						}
						if (timeStep == 49)
							AttackedFromAMforTank.enqueue(Et);//List for printing the last attacked ET by AM
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
		if (ad1 && ad2)
		{
			if (timeStep == 49) {
				AttackedFromADforGunnery.enqueue(Ad1);//the attacker units
				AttackedFromADforGunnery.enqueue(Ad2);//the attacker units
			}
		if (Ad1->getAttackCap() < Ad2->getAttackCap()) capacity = Ad1->getAttackCap();
		else capacity = Ad2->getAttackCap();
	
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
					if(timeStep==49)
					AttackedFromADforGunnery.enqueue(Eg);//List for printing the last attacked EG by AD
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
							counterForUML2++;
						}
						else
						{
							TempList.enqueue(Et);
						}
						if (timeStep == 49)
							AttackedFromADforTank.enqueue(Et);//List for printing the last attacked Et by AD
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





	HealLogic();


	if (timeStep == 49) {
		char f[] = "youssef";
		CreateOutputFile(f, AttackedFromES, AttackedFromETforMonster, AttackedFromETforSoilder, AttackedFromEGforMonster, AttackedFromEGforDrones
			, AttackedFromAS, AttackedFromAMforSoilder, AttackedFromAMforTank, AttackedFromADforGunnery, AttackedFromADforTank);
	}
	printQueues(AttackedFromES, AttackedFromETforMonster, AttackedFromETforSoilder, AttackedFromEGforMonster, AttackedFromEGforDrones
		, AttackedFromAS, AttackedFromAMforSoilder, AttackedFromAMforTank, AttackedFromADforGunnery, AttackedFromADforTank);
}

void Game::HealLogic() {
	LinkedQueue<Unit*>TempListforsoilder;
	LinkedQueue<Unit*>TempListfortank;
	int f;
	Unit* healunit = nullptr,*healed=nullptr;

	if (earthArmy.RemoveHealUnit(healunit)) 
		for (int i = 0; i < healunit->getAttackCap(); i++) {
			if (Uml1.dequeue(healed, f)) {
				counterForUML1--;
				if (timeStep - healed->gettimeUml() > 10) {
					addToKilledList(healed);
					i--;
					continue;
				}
				healunit->Attack(healed);
				num_of_healed++;
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
				counterForUML2--;
				if (timeStep - healed->gettimeUml() > 10) {
					addToKilledList(healed);
					i--;
					continue;
				}
				healunit->Attack(healed);
				num_of_healed++;
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
	while (TempListfortank.dequeue(deleter)) {
		Uml2.enqueue(deleter);
		counterForUML2++;
	}
	
	while (TempListforsoilder.dequeue(deleter)) {
		Uml1.enqueue(deleter, 10000 - deleter->getHealth());
		counterForUML1++;
	}
	
}

void Game::printQueues(LinkedQueue<Unit*>AfromEs, LinkedQueue<Unit*>AfromEtforAm, LinkedQueue<Unit*>AfromEtforAs, LinkedQueue<Unit*>AfromEgforAm,
	LinkedQueue<Unit*>AfromEgforAd, LinkedQueue<Unit*>AfromAs, LinkedQueue<Unit*>AfromAmforEs, LinkedQueue<Unit*>AfromAmforEt
	, LinkedQueue<Unit*>AfromAdforEg, LinkedQueue<Unit*>AfromAdforEt){

	
	cout << "Current Timestep " << timeStep << endl;//cout current time Step
	cout << "============== Earth Army Alive Units ============== " << endl;//printing earth army lists
	earthArmy.printEarthSoldiers();
	earthArmy.printEarthTanks();
	earthArmy.printEarthGunnerys();
	cout << endl;
	cout << "============== Alien Army Alive Units ============== " << endl;//printing alien army lists
	alienArmy.printAlienSoldiers();
	alienArmy.printAlienDrones();
	alienArmy.printAlienMonsters();
	
	cout << endl<<"==================== HealList ====================="<<endl;
	earthArmy.printHealUnits();
	cout <<endl;

	cout << endl << "====================== Unit Maintenance List ===============" << endl;
	printUML();
	cout << endl;

	cout << "===================== Units fighting at current step ===============" << endl;
//Attacked from earth soilder
	Unit* Es = nullptr, * Et = nullptr, * Eg = nullptr, * As = nullptr, * Am = nullptr,*Ad1=nullptr,*Ad2=nullptr;
	if (AfromEs.dequeue(Es)) {
		cout << "ES " << Es->getID() << " shots ";
		cout << "[";
		AfromEs.print_the_list();
		cout << "]" << endl;
	}
	//Attacked from earth tank
	if (AfromEtforAm.dequeue(Et)) {
		cout << "ET " << Et->getID() << " shots ";
		cout << "[";
		AfromEtforAm.print_the_list();
		cout << "] && [";
		AfromEtforAs.print_the_list();
		cout << "]" << endl;
	}
	//Attacked from earth Gunnery
	if (AfromEgforAm.dequeue(Eg)) {
		cout << "EG " << Eg->getID() << " shots ";
		cout << "[";
		AfromEgforAm.print_the_list();
		cout << "] && [";
		AfromEgforAd.print_the_list();
		cout << "]" << endl;
	}
	//Attacked from alien soilder
	if (AfromAs.dequeue(As)) {
		cout << "AS " << As->getID() << " shots ";
		cout << "[";
		AfromAs.print_the_list();
		cout << "]" << endl;
	}
	//Attacked from alien monster
	if (AfromAmforEs.dequeue(Am)) {
		cout << "AM " << Am->getID() << " shots ";
		cout << "[";
		AfromAmforEs.print_the_list();
		cout << "] && [";
		AfromAmforEt.print_the_list();
		cout << "]" << endl;
	}
	//Attacked from alien drones
	if (AfromAdforEg.dequeue(Ad1)&& AfromAdforEg.dequeue(Ad2)) {
		cout << "AD " << Ad1->getID()<<" && "<< Ad2->getID()<< " shots ";
		cout << "[";
		AfromAdforEg.print_the_list();
		cout << "] && [";
		AfromAdforEt.print_the_list();
		cout << "]" << endl;
	}
	cout << endl;
	cout << "============== Killed/Destructed Units ============= " << endl;
	PrintKilledList();//printing the killed list of units
}

void Game::printUML() {
	cout << counterForUML1 << " ES [";
	Uml1.print_the_list();
	cout << "]"<<endl;
	cout << counterForUML2 << " ET [";
	Uml2.print_the_list();
	cout << "]" << endl;
}

void Game::CreateOutputFile(char filename[],LinkedQueue<Unit*>AfromEs, LinkedQueue<Unit*>AfromEtforAm, LinkedQueue<Unit*>AfromEtforAs, LinkedQueue<Unit*>AfromEgforAm,
	LinkedQueue<Unit*>AfromEgforAd, LinkedQueue<Unit*>AfromAs, LinkedQueue<Unit*>AfromAmforEs, LinkedQueue<Unit*>AfromAmforEt
	, LinkedQueue<Unit*>AfromAdforEg, LinkedQueue<Unit*>AfromAdforEt) {
	char filePath[100];
	ofstream file;

	for (int i = 0; i < strlen(filename); i++)
		filePath[i] = filename[i];
	filePath[strlen(filename)] = '.';
	filePath[strlen(filename) + 1] = 't';
	filePath[strlen(filename) + 2] = 'x';
	filePath[strlen(filename) + 3] = 't';
	filePath[strlen(filename) + 4] = '\0';

	file.open(filePath, ios::out);

	Unit* forascending = nullptr;
	priQueue<Unit*> ascending;//ascendingly by td
	LinkedQueue<Unit*> collect;//i make it to return the values to killed List
	while (KilledList.dequeue(forascending)) {
		ascending.enqueue(forascending, 10000 - forascending->getTd());
		collect.enqueue(forascending);
	}
	while (collect.dequeue(forascending))
		KilledList.enqueue(forascending);

	int f = 0;
	int Df, Dd, Db;
	int Total_Df_E=0, Total_Dd_E=0, Total_Db_E=0,counter_E_for_Ave=0;
	int Total_Df_A = 0, Total_Dd_A = 0, Total_Db_A = 0, counter_A_for_Ave=0;
	while (ascending.dequeue(forascending, f)) {//printing the Killed List  ascendingly by Td
		file << "Td  ID  Tj  Df  Dd  Db" << endl;
		file << forascending->getTd();
		if(forascending->getTd() > 9)
			file <<"  ";
		else
			file << "   ";
		
		file << forascending->getID();
		if (forascending->getID() > 9)
			file << "  ";
		else
			file << "   ";
		
		file << forascending->getTj();
		if (forascending->getTj() > 9)
			file << "  ";
		else
			file << "   ";
	
		Df = forascending->getTa() - forascending->getTj();
		file <<Df;
		if (Df > 9)
			file << "  ";
		else
			file << "   ";

		Dd = forascending->getTd() - forascending->getTa();
		file <<Dd;
		if (Dd > 9)
			file << "  ";
		else
			file << "   ";

		Db = forascending->getTd() - forascending->getTj();
		file <<Db;
		if (Db > 9)
			file << "  ";
		else
			file << "   ";
		file << endl << endl;
		if (forascending->getTYPE() == 0 || forascending->getTYPE() == 1 || forascending->getTYPE() == 2) {
			Total_Df_E += Df;
			Total_Dd_E += Dd; 
			Total_Db_E += Db;
			counter_E_for_Ave++;
		}
		else {
			Total_Df_A += Df;
			Total_Dd_A += Dd;
			Total_Db_A += Db;
			counter_A_for_Ave++;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////

	int eartharmyunits = earthArmy.getEScount() + counterForUML1 + killedcountEs + earthArmy.getETcount() + counterForUML2 + killedcountEt +
		earthArmy.getEGcount() + killedcountEg;

	file << "================= Earth Army =================" << endl;
	file << "Battle Result:";
	int earthcount = earthArmy.getEScount() + earthArmy.getEGcount() + earthArmy.getETcount();
	int aliencount = alienArmy.getADcount() + alienArmy.getAMcount() + alienArmy.getAScount();
	if (earthcount == 0 && aliencount == 0)
		file << "  Drawn" << endl;
	else if (earthcount == 0)
		file << "  Loss" << endl;
	else if (aliencount == 0)
		file << "  Win"<<endl;
	else
		file << "  Drawn" << endl;
	file  << endl;
	file <<"Total_Es = " << earthArmy.getEScount() + counterForUML1 + killedcountEs<<endl;
	file << "Total_Et = " << earthArmy.getETcount() + counterForUML2 + killedcountEt << endl;
	file << "Total_Eg = " << earthArmy.getEGcount() + killedcountEg << endl<<endl;


	double percentage1 = 0, percentage2 = 0, percentage3 = 0;
	percentage1 = ((double)killedcountEs / (earthArmy.getEScount() + counterForUML1 + killedcountEs));
	file << "Es_Destructed/Es_Total = " << percentage1 * 100 << "%" << endl;
	percentage2 = ((double)killedcountEt / (earthArmy.getETcount() + counterForUML2 + killedcountEt));
	file << "Et_Destructed/Et_Total = " << percentage2 * 100 << "%" << endl;
	percentage3 = ((double)killedcountEg / (earthArmy.getEGcount() + killedcountEg));
	file << "Eg_Destructed/Eg_Total = " << percentage3 * 100 << "%" << endl;

	int destructed_Earth = killedcountEs + killedcountEt + killedcountEg;

	file << "Total_Destructed/Total_Units = " << ((double)destructed_Earth/eartharmyunits )*100<<"%" << endl << endl;
	if (counter_E_for_Ave > 0) {
		file << "Average_of_DF = " << (double)Total_Df_E / counter_E_for_Ave << endl;
		file << "Average_of_Dd = " << (double)Total_Dd_E / counter_E_for_Ave << endl;
		file << "Average_of_Db = " << (double)Total_Db_E / counter_E_for_Ave << endl << endl;
	}
	else {
		file << "Average_of_DF = " << "Not defined" << endl;
		file << "Average_of_Dd = " << "Not defined" << endl;
		file << "Average_of_Db = " << "Not defined" << endl << endl;
	}
	if (Total_Db_E > 0) {
		file << "Df/Db = " << (double)Total_Df_E / Total_Db_E << "%" << endl;
		file << "Dd/Db = " << (double)Total_Dd_E / Total_Db_E << "%" << endl << endl;
	}
	else {
		file << "Df/Db = " << "Not defined" << endl;
		file << "Dd/Db = " << "Not defined" << endl << endl;
	}

	file << "Healed_successfully/Total_Earth = " << (double)num_of_healed / eartharmyunits << "%" << endl << endl;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	int alienarmyunits = alienArmy.getAScount() + killedcountAs + alienArmy.getAMcount() + killedcountAm + alienArmy.getADcount() + killedcountAd;

	file << "============== Alien Army ============" << endl;
	file << "Battle Result:";
	if (earthcount == 0 && aliencount == 0)
		file << "  Drawn" << endl;
	else if (earthcount == 0)
		file << "  Win" << endl;
	else if (aliencount == 0)
		file << "  Loss" << endl;
	else
		file << "  Drawn" << endl;
	file << endl;

	file << "Total_AS = " << alienArmy.getAScount() + killedcountAs << endl;
	file << "Total_AM = " << alienArmy.getAMcount() + killedcountAm << endl;
	file << "Total_AD = " << alienArmy.getADcount() + killedcountAd << endl << endl;



	percentage1 = ((double)killedcountAs / (alienArmy.getAScount() + killedcountAs));
	file << "As_Destructed/As_Total = " << percentage1 * 100 << "%" << endl;
	percentage2 = ((double)killedcountAm / (alienArmy.getAMcount() + killedcountAm));
	file << "Am_Destructed/Am_Total = " << percentage2 * 100 << "%" << endl;
	percentage3 = ((double)killedcountAd / (alienArmy.getADcount() + killedcountAd));
	file << "Ad_Destructed/Ad_Total = " << percentage3 * 100 << "%" << endl;

	file << "Total_Destructed/Total_Units = " << ((double)(killedCount-destructed_Earth) / alienarmyunits) * 100 << "%" << endl << endl;
	if (counter_A_for_Ave > 0) {
		file << "Average_of_DF = " << (double)Total_Df_A / counter_A_for_Ave << endl;
		file << "Average_of_Dd = " << (double)Total_Dd_A / counter_A_for_Ave << endl;
		file << "Average_of_Db = " << (double)Total_Db_A / counter_A_for_Ave << endl << endl;
	}
	else {
		file << "Average_of_DF = " << "Not defined" << endl;
		file << "Average_of_Dd = " << "Not defined" << endl;
		file << "Average_of_Db = " << "Not defined" << endl << endl;
	}
	if (Total_Db_A > 0) {
		file << "Df/Db = " << (double)Total_Df_A / Total_Db_A << "%" << endl;
		file << "Dd/Db = " << (double)Total_Dd_A / Total_Db_A << "%" << endl << endl;
	}
	else {
		file << "Df/Db = " << "Not defined" << endl;
		file << "Dd/Db = " << "Not defined" << endl << endl;
	}
	file.close();
}