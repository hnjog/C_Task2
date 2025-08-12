#include "Util.h"
#include "Character.h"
#include "Skill.h"
#include <iostream>

Character::Character()
	: Character(0, 0, 0, 0, string{})
{
}

Character::Character(int maxHp, int maxMp, int attack, int defense, string name)
	: CurrentHp(maxHp),
	CurrentMp(maxMp),
	BaseStat(new Stats{ maxHp, maxMp, attack, defense }),
	EnhancedStat(new Stats{}),
	Name(move(name))
{
}

// 이러면 move(name)이 결과적으로 2번 이루어지지만,
// 사실 함수 지역 변수에 string 의 이동 생성자로 그 값이 들어가기에 타입상 문제가 없어보임
// 지역변수 name <- move(외부 outername) 
Character::Character(const Stats& stats, string name)
	:Character(stats.MaxHp, stats.MaxMp, stats.Attack, stats.Defense, move(name))
{
}

Character::~Character()
{
	Skills.clear();
	SafeDelete(BaseStat);
	SafeDelete(EnhancedStat);
}

void Character::Attack(Character* Other, SkillIdx skillIdx)
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

void Character::Hit(int damage)
{
	CurrentHp -= (damage - GetDefense());
}

void Character::AddSkill(SkillIdx skillIdx, Skill&& skill)
{
	Skills[skillIdx] = move(skill);
}

void Character::HealHp(int amount)
{
	if (amount <= 0)
		return;

	if (FullHp())
		return;

	int healAmount = amount;
	CurrentHp += healAmount;
	if (CurrentHp > GetMaxHp())
	{
		healAmount = amount - (CurrentHp - GetMaxHp());
		CurrentHp = GetMaxHp();
	}

	cout << "* HP가 " << healAmount << " 회복되었습니다.";
}

void Character::RefreshMp(int amount)
{
	if (amount <= 0)
		return;

	if (FullMp())
		return;

	int refreshAmount = amount;
	CurrentMp += amount;
	if (CurrentMp > GetMaxMp())
	{
		refreshAmount = amount - (CurrentMp - GetMaxMp());
		CurrentMp = GetMaxMp();
	}

	cout << "* HP가 " << refreshAmount << " 회복되었습니다.";
}

void Character::BoostDoubleMaxHp()
{
	int targetHp = GetMaxHp() << 1; // * 2
	int baseHp = BaseStat->MaxHp;

	EnhancedStat->MaxHp = targetHp - baseHp;
	CurrentHp *= 2;
	cout << "* HP가 2배로 증가되었습니다." << '\n';
}

void Character::BoostDoubleMaxMp()
{
	int targetMp = GetMaxMp() << 1;
	int baseMp = BaseStat->MaxMp;

	EnhancedStat->MaxMp = targetMp - baseMp;
	CurrentMp *= 2;
	cout << "* MP가 2배로 증가되었습니다." << '\n';
}
