#pragma once
#include "Character.h"
class Monster :
    public Character
{
public:
    virtual void Attack(Character* Other, SkillIdx skillIdx) override;
    virtual void Hit(Character* Hitter, int damage) override;
};

