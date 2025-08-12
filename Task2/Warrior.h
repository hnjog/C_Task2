#pragma once
#include "Player.h"
class Warrior :
    public Player
{
public:
    virtual void Attack(Character* Other, SkillIdx skillIdx) override;
};

