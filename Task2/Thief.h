#pragma once
#include "Player.h"
class Thief :
    public Player
{
public:
    virtual void Attack(Character* Other, SkillIdx skillIdx) override;
};

