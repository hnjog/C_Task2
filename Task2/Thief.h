#pragma once

#include "Player.h"

class Thief : public Player
{
public:
	Thief();
	Thief(int maxHp, int maxMp, int attack, int defense, int accuracy, int speed, string name);
	Thief(const Stats& stats, string name);
	virtual ~Thief();

public:
	virtual void Attack(Character* Other, SkillIdx skillIdx) override;

protected:
	int AttackCount;
};

