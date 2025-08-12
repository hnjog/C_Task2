#include "Magician.h"
#include "Util.h"
#include "Enums.h"
#include "Skill.h"
#include <iostream>
#include <unordered_map>

Magician::Magician()
	:Player(),
	AddSkillRate(1.2)
{
	MyClass = CLI_Magician;
}

Magician::Magician(int maxHp, int maxMp, int attack, int defense, int accuracy, int speed, string name)
	:Player(maxHp, maxMp, attack, defense, accuracy, speed, name),
	AddSkillRate(1.2)
{
	MyClass = CLI_Magician;
}

Magician::Magician(const Stats& stats, string name)
	:Player(stats, name),
	AddSkillRate(1.2)
{
	MyClass = CLI_Magician;
}

Magician::~Magician()
{
}

void Magician::Attack(Character* Other, SkillIdx skillIdx)
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

	cout << "마법사 공격 시 추가 스킬 공격력을 가집니다!" << '\n';

	int nowDamage = static_cast<int>((Skills[skillIdx].DamageRate + AddSkillRate) * static_cast<double>(GetAttack()));

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
