#pragma once
#include "Player.h"
class Magician :
    public Player
{
public:
    virtual void Attack(Character* Other, SkillIdx skillIdx) override;
};

