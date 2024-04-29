#pragma once
#include<iostream>
using namespace std;





class Unit {
private:
	enum TYPE {ES,ET,EG,AS,AM,AD};
	int ID;
	int Tj,Health,Power;
	int AttackCap;
	int type;
public:
	Unit(double h=0, double pw=0, double AC=0, int tj=0);
	virtual void Attack() =0;
	void setID(int id);
	void settype(int t);
	void setPower(int p);
	void setHealth(int h);
	int getID()const;
	void setTJ(int t);
	int getPower()const;
	int getHealth()const;
	int getTYPE()const;
	void setAttackCap(int x);
	int getAttackCap()const;
	friend ostream& operator << (ostream& , Unit *u);
};


  