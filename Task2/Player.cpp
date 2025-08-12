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
	MyClass(ClassIdx::CLI_Nobiss),
	Level(1)
{
}

Player::Player(int maxHp, int maxMp, int attack, int defense, int accuracy, int speed, string name)
	:Character(maxHp, maxMp, attack, defense,accuracy,speed, name),
	MyInventory(new Inventory(this)),
	MyClass(ClassIdx::CLI_Nobiss),
	Level(1)
{
}

Player::Player(const Stats& stats, string name)
	:Character(stats,name),
	MyInventory(new Inventory(this)),
	MyClass(ClassIdx::CLI_Nobiss),
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

	Other->Hit(this,nowDamage);
}

void Player::Hit(Character* Hitter, int damage)
{
	if (IsNotValid(Hitter))
		return;

	int damageResult = (damage - GetDefense());
	if (damageResult <= 0)
		damageResult = 1;
	CurrentHp -= damageResult;

	cout << Hitter->GetName() << "에게 공격받음!" << '\n';
	cout << "총 대미지 : " << damageResult << '\n';
	cout << GetName() << "의 현재 체력 : " << GetNowHp() << '\n';
}

string Player::GetJobName()
{
	switch (MyClass)
	{
	case CLI_Nobiss:
		return "초보자";
	case CLI_Warrior:
		return "전사";
	case CLI_Magician:
		return "마법사";
	case CLI_Thief:
		return "도적";
	case CLI_Archer:
		return "궁수";
	case CLI_ClassMax:
	default:
		break;
	}

	return "뭔가 잘못됐는대요?";
}

void Player::PrintPlayerStatus()
{
	cout << "------------------------------------" << endl;
	cout << "* 현재 능력치" << endl;
	cout << "닉네임: " << Name << endl;
	cout << "직업: " << GetJobName() << endl;
	cout << "Lv. " << Level << endl;
	cout << "HP: " << GetNowHp() << endl;
	cout << "MP: " << GetNowMp() << endl;
	cout << "공격력: " << GetAttack() << endl;
	cout << "방어력: " << GetDefense() << endl;
	cout << "정확도: " << GetAccuracy() << endl;
	cout << "속도: " << GetSpeed() << endl;
	cout << "------------------------------------" << endl;
}
