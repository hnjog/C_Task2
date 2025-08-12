#pragma once

#include "Player.h"

class Warrior : public Player
{
public:
	Warrior();
	Warrior(int maxHp, int maxMp, int attack, int defense, int accuracy, int speed, string name);
	Warrior(const Stats& stats, string name);
	virtual ~Warrior();

public:
    virtual void Attack(Character* Other, SkillIdx skillIdx) override;

protected:
	int AddDamage;

};

