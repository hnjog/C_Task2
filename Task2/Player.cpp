#include "Player.h"
#include "Inventory.h"
#include "Util.h"
#include "Enums.h"
#include "Skill.h"
#include <iostream>
#include <unordered_map>

Player::Player()
	:Character(),
	MyInventory(new Inventory(this))
{
}

Player::Player(int maxHp, int maxMp, int attack, int defense, string name)
	:Character(maxHp, maxMp, attack, defense, name),
	MyInventory(new Inventory(this))
{
}

Player::Player(const Stats& stats, string name)
	:Character(stats,name),
	MyInventory(new Inventory(this))
{
}

Player::~Player()
{
	SafeDelete(MyInventory);
}

void Player::GetItem(ItemIdx item, int count)
{
	if (IsNotValid(MyInventory))
	{
		return;
	}

	MyInventory->AddItem(item, count);
}

void Player::UseItem(ItemIdx item)
{
	if (IsNotValid(MyInventory))
	{
		return;
	}

	MyInventory->UseItem(item, this);
}

int Player::GetItemCount(ItemIdx item)
{
	if (IsNotValid(MyInventory))
	{
		return 0;
	}

	return MyInventory->GetItemCount(item);
}
