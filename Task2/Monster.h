#pragma once
#include "Character.h"
class Monster :
    public Character
{
public:
    Monster();
    Monster(int maxHp, int maxMp, int attack, int defense, int accuracy, int speed, string name);
    Monster(const Stats& stats, string name);
    virtual ~Monster();

public:
    virtual void Attack(Character* Other, SkillIdx skillIdx) override;
    virtual void Hit(Character* Hitter, int damage) override;
};

