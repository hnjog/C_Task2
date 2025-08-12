#include "Monster.h"
#include "Util.h"
#include "Enums.h"
#include "Skill.h"
#include <iostream>
#include <unordered_map>
#include"Player.h"

void Monster::Attack(Character* Other, SkillIdx skillIdx)
{
	int nowDamage = static_cast<int>(Skills[skillIdx].DamageRate * static_cast<double>(GetAttack()));
	// Monster�� ������ Mp ��� ���� ���� ���� ����
	Other->Hit(this,nowDamage);
}

void Monster::Hit(Character* Hitter, int damage)
{
	// ���� �¶��� ���ӿ��� hitter �� ������� �������� �޴� ��찡 ���� ����
	// �ٸ� ������ dead ���·� ó���ϱ⿡ �����ϱ� ������
	// �� �̵��ϸ� �����ϴ� ���� ��Ȳ�� �����ϴ� ��� ���� ����ϴ� ��?
	if (IsNotValid(Hitter))
		return;

	int damageResult = (damage - GetDefense());
	if (damageResult <= 0)
		damageResult = 1;
	CurrentHp -= damageResult;

	cout << Hitter->GetName() << "���� ���ݹ���!" << '\n';
	cout << "�� ����� : " << damageResult << '\n';
	cout << GetName() << "�� ���� ü�� : " << GetNowHp() << '\n';
}
