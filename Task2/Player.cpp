#include "Player.h"
#include "Inventory.h"
#include "Util.h"
#include "Enums.h"
#include "Skill.h"
#include <iostream>
#include <unordered_map>

Player::Player()
	:Character(),
	MyInventory(new Inventory(this)),
	MyClass(ClassIdx::Nobiss),
	Level(1)
{
}

Player::Player(int maxHp, int maxMp, int attack, int defense, int accuracy, int speed, string name)
	:Character(maxHp, maxMp, attack, defense,accuracy,speed, name),
	MyInventory(new Inventory(this)),
	MyClass(ClassIdx::Nobiss),
	Level(1)
{
}

Player::Player(const Stats& stats, string name)
	:Character(stats,name),
	MyInventory(new Inventory(this)),
	MyClass(ClassIdx::Nobiss),
	Level(1)
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

void Player::Attack(Character* Other, SkillIdx skillIdx)
{
	if (skillIdx >= SkillIdx::SkillMax)
	{
		return;
	}

	if (Skills.find(skillIdx) == Skills.end())
	{
		cout << "존재하지 않는 스킬입니다!" << '\n';
		return;
	}

	if (Skills[skillIdx].RequireMp > CurrentMp)
	{
		cout << "스킬 사용이 불가합니다." << '\n';
		return;
	}

	int nowDamage = static_cast<int>(Skills[skillIdx].DamageRate * static_cast<double>(GetAttack()));

	switch (skillIdx)
	{
	case BaseAttack:
	{
		CurrentMp -= Skills[skillIdx].RequireMp;
		cout << "* 스킬을 사용하여 MP가 " << Skills[skillIdx].RequireMp << " 소모되었습니다." << '\n';
		cout << Name << "의 현재 MP : " << CurrentMp << '\n';
	}
	break;
	case LethalAttack:
	{
		CurrentMp /= 2;
		cout << "* 스킬을 사용하여 MP가 50% 소모되었습니다." << '\n';
		cout << Name << "의 현재 MP : " << CurrentMp << '\n';
	}
	break;
	}

	Other->Hit(nowDamage);
}

void Player::Hit(int damage)
{
	CurrentHp -= (damage - GetDefense());
}

string Player::GetJobName()
{
	switch (MyClass)
	{
	case Nobiss:
		return "Nobiss";
	case Warrior:
		return "Warrior";
	case Magician:
		return "Magician";
	case Thief:
		return "Thief";
	case Archer:
		return "Archer";
	case ClassMax:
	default:
		break;
	}

	return "SomeThingIsWrong";
}
