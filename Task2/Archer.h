#pragma once
#include "Player.h"
class Archer :
    public Player
{
public:
    virtual void Attack(Character* Other, SkillIdx skillIdx) override;
};

