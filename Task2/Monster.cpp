#include "Monster.h"
#include "Util.h"
#include "Enums.h"
#include "Skill.h"
#include <iostream>
#include <unordered_map>
#include"Player.h"

Monster::Monster()
	:Character()
{
}

Monster::Monster(int maxHp, int maxMp, int attack, int defense, int accuracy, int speed, string name)
	:Character(maxHp, maxMp, attack, defense, accuracy, speed, name)
{
}

Monster::Monster(const Stats& stats, string name)
	:Character(stats, name)
{
}

Monster::~Monster()
{
}

void Monster::Attack(Character* Other, SkillIdx skillIdx)
{
	int nowDamage = static_cast<int>(Skills[skillIdx].DamageRate * static_cast<double>(GetAttack()));
	// Monster의 별도의 Mp 계산 등은 하지 않을 예정
	Other->Hit(this,nowDamage);
}

void Monster::Hit(Character* Hitter, int damage)
{
	// 실제 온라인 게임에선 hitter 가 사라져도 데미지를 받는 경우가 종종 있음
	// 다만 보통은 dead 상태로 처리하기에 안전하긴 하지만
	// 맵 이동하며 공격하는 등의 상황을 방지하는 경우 등을 고려하는 듯?
	if (IsNotValid(Hitter))
		return;

	int damageResult = (damage - GetDefense());
	if (damageResult <= 0)
		damageResult = 1;

	CurrentHp -= damageResult;

	if (CurrentHp < 0)
		CurrentHp = 0;

	cout << Hitter->GetName() << "에게 공격받음!" << '\n';
	cout << "총 대미지 : " << damageResult << '\n';
	cout << GetName() << "의 현재 체력 : " << GetNowHp() << '\n';
}
