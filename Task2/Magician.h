#pragma once
#include "Player.h"
class Magician :
    public Player
{
public:
	Magician();
	Magician(int maxHp, int maxMp, int attack, int defense, int accuracy, int speed, string name);
	Magician(const Stats& stats, string name);
	virtual ~Magician();
public:
	virtual void Attack(Character* Other, SkillIdx skillIdx) override;

public:
	double AddSkillRate;

};

