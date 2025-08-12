#include "Thief.h"
#include "Util.h"
#include "Enums.h"
#include "Skill.h"
#include <iostream>
#include <unordered_map>

void Thief::Attack(Character* Other, SkillIdx skillIdx)
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

	const int AttackCount = 5;
	cout << "도적은 총 대미지의 " << AttackCount << "분의 1로 " << AttackCount << "만큼 연타합니다!" << '\n';
	for(int i = 0; i < AttackCount;i++)
		Other->Hit(nowDamage / AttackCount);
}
