#pragma once
#include "Player.h"
class Archer :
    public Player
{
public:
	Archer();
	Archer(int maxHp, int maxMp, int attack, int defense, int accuracy, int speed, string name);
	Archer(const Stats& stats, string name);
	virtual ~Archer();
public:
	virtual void Attack(Character* Other, SkillIdx skillIdx) override;

public:
	int AttackCount;
};

