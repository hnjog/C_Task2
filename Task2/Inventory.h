#pragma once

#include"Enums.h"
#include<unordered_map>

using namespace std;

class Character;

struct Item
{
	int ItemCount; // 아이템 개수
	EffectIdx Effect; // 효과
};

class Inventory
{
public:
	Inventory(Character* owner);
	virtual ~Inventory();

public:
	void AddItem(ItemIdx itemIdx, int count);
	bool UseItem(ItemIdx itemIdx, Character* Target);

	int GetItemCount(ItemIdx itemIdx);

protected:
	bool Effect(EffectIdx effectIdx, Character* Target);

protected:
	unordered_map<ItemIdx, Item> ItemMap;

	Character* Owner;
};