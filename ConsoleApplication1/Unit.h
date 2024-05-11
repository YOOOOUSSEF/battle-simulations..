#pragma once
#include<iostream>
using namespace std;





class Unit {
private:
	enum TYPE {ES,ET,EG,AS,AM,AD,HU};
	int ID;
	int Tj,Ta,Td,Health,Power;
	int AttackCap;
	int type;
	int initialhealth,timeUml;
public:
	Unit(double h=0, double pw=0, double AC=0, int tj=0);
	virtual void Attack(Unit*&);
	void setID(int id);
	void settype(int t);
	void setPower(int p);
	void setHealth(int h);
	int getID()const;
	void setTJ(int t);
	void setTa(int t);
	void setTd(int t);
	int getTa()const;
	int getTd()const;
	int getTj()const;
	int getPower()const;
	int getHealth()const;
	int getTYPE()const;
	void setAttackCap(int x);
	int getAttackCap()const;
	int getinitialhealth()const;
	void setinitialhealth(int);
	int gettimeUml()const;
	void settimeUml(int);
	friend ostream& operator << (ostream& , Unit *u);
};


  