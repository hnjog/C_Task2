#pragma once

// 실제 개발시에는 이 둘에 대한 매핑이 더 잘되어 있어야 한다
enum ItemIdx
{
	HealthPotion,
	ManaPotion,
	ItemMax,
};

enum EffectIdx
{
	HealHp,
	ManaRefrain,
	EffectMax,
};

enum SkillIdx
{
	BaseAttack,
	LethalAttack,
	SkillMax,
};