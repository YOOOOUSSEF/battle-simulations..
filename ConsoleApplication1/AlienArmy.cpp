#include "AlienArmy.h"

AlienArmy::AlienArmy()
{
	//intializtion of alienArmy Data members
	id = 2000;
	AScount = 0;
	ADcount = 0;
	AMcount = 0;
}

void AlienArmy::addAlienSoldier(Unit* Soldier)
{
	AlienSoldiers.enqueue(Soldier);//calling the enqueue function of the queue of aliensoliders
	if (Soldier->getID() == -1)//checking that we have a new Unit
	{
		Soldier->setID(id);
		id++;
	}
	AScount++;//increment the aliensoldiers count
}

void AlienArmy::addAlienDrone(Unit* Drone)
{
	AlienDrones.enqueue(Drone); // calling the enqueue function of the queue of alienDrones
	if (Drone->getID() == -1)
	{
		Drone->setID(id);
		id++;
	}
	ADcount++;
}
void AlienArmy::addAlienDroneFirst(Unit* Drone) {
	AlienDrones.enqueuefirst(Drone); // calling the enqueue function of the queue of alienDrones
	if (Drone->getID() == -1)
	{
		Drone->setID(id);
		id++;
	}
	ADcount++;
}

bool AlienArmy::addAlienMonster(Unit* Monster)
{

	if (AMcount == MAX_LEN)//if the array of monster became full
		return false;
	else
	{
		AlienMonsters[AMcount] = Monster;
		if (Monster->getID() == -1)
		{
			AlienMonsters[AMcount]->setID(id);
			id++;
		}
		AMcount++;//we don't need to save the order of monster so we add it it the last 
		//empty location to make adding operation in time complexcity of O(1)
		
	}
	return true;
}

bool AlienArmy::RemoveAlienSoldier(Unit*& Soldier)
{
	if (AScount == 0)
	{
		Soldier = NULL;
		return 0;
	}
	else {
		AlienSoldiers.dequeue(Soldier);
		AScount--;
		return true;
	}
}
bool AlienArmy::RemoveAlienDroneFirst(Unit*& Drone)
{

	if (ADcount == 0)
	{
		Drone = NULL;
		return false;
	}
	AlienDrones.dequeue(Drone);
	ADcount--;
	return true;
	
}
bool AlienArmy::RemoveAlienDroneLast(Unit*& Drone)
{
	if (ADcount == 0)
	{
		Drone = NULL;
		return false;
	}
	AlienDrones.dequeuelast(Drone);
	ADcount--;
	return true;
	
}

bool AlienArmy::RemoveAlienMonster(Unit*& Monster)
{
	if (AMcount == 0)
	{
		Monster = NULL;
		return false;
	}
	else//notice:we get a radom Monster
	{
		int randomIndex = rand() % (AMcount);//we will get a random index to get a random monster
		//range of the random Index is from 0 to currentSize - 1
		Monster = AlienMonsters[randomIndex];
		AlienMonsters[randomIndex] = AlienMonsters[AMcount - 1];  
		AMcount--;
	}
	return true;
}

void AlienArmy::printAlienSoldiers()
{
	cout << AScount << " AS [";
	AlienSoldiers.print_the_list();
	cout << "] ";
	cout << endl;
}

void AlienArmy::printAlienDrones()
{
	cout << ADcount << " AD [";
	AlienDrones.print();
	cout << "] ";
	cout << endl;
}

void AlienArmy::printAlienMonsters()
{
	cout << AMcount << " AM [";
	for (int i = 0; i < AMcount-1; i++)
		cout << AlienMonsters[i] << " ,";
	if(AMcount>0)
	cout << AlienMonsters[AMcount-1];
	cout << "] ";
	cout << endl;
}

int AlienArmy::getAScount()
{
	return AScount;
}

int AlienArmy::getADcount()
{
	return ADcount;
}

int AlienArmy::getAMcount()
{
	return AMcount;
}

void AlienArmy::SetAScount(int x)
{
	AScount = x;
}

void AlienArmy::SetADcount(int x)
{
	ADcount = x;
}

void AlienArmy::SetAMcount(int x)
{

	AMcount = x;
}

AlienArmy::~AlienArmy()
{
	Unit* Delete;
	while (!AlienSoldiers.isEmpty())
	{
		AlienSoldiers.dequeue(Delete);//deleting the queue
		delete Delete;
	}
	
	while (!AlienDrones.isEmpty())
	{
		AlienDrones.dequeue(Delete);//deleting the doubly linked queue
		delete Delete;
	}

	for (int i = 0; i < AMcount; i++)
	{
		delete AlienMonsters[i];//deleting the array
	}

	id = 2000;
	AScount = 0;
	ADcount = 0;
	AMcount = 0;
	
}
