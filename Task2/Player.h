#pragma once
#include "Character.h"
#include "Enums.h"

class Inventory;

class Player :
    public Character
{
public:
	Player();
	Player(int maxHp, int maxMp, int attack, int defense, string name);
	Player(const Stats& stats, string name);
	virtual ~Player();

public:
	void GetItem(ItemIdx item, int count);
	void UseItem(ItemIdx item);

	int GetItemCount(ItemIdx item);

	inline void HalfHp() { CurrentHp = GetMaxHp() / 2; }
	inline void HalfMp() { CurrentMp = GetMaxMp() / 2; }

protected:
	Inventory* MyInventory;

};

