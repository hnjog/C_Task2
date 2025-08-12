#pragma once

#include <unordered_map>
#include <string>
#include "Enums.h"

using namespace std;

class Skill;

struct Stats
{
	int MaxHp;
	int MaxMp;
	int Attack;
	int Defense;

	Stats()
	{
		MaxHp = 0;
		MaxMp = 0;
		Attack = 0;
		Defense = 0;
	}

	Stats(int maxHp,int maxMp, int attack, int defense)
	{
		MaxHp = maxHp;
		MaxMp = maxMp;
		Attack = attack;
		Defense = defense;
	}

};

class Character
{
public:
	Character();
	Character(int maxHp, int maxMp, int attack, int defense, string name);
	Character(const Stats& stats, string name);
	virtual ~Character();

	virtual void Attack(Character* Other, SkillIdx skillIdx);
	virtual void Hit(int damage);

	void AddSkill(SkillIdx skillIdx, Skill&& skill);

	void HealHp(int amount);
	void RefreshMp(int amount);

	void BoostDoubleMaxHp();
	void BoostDoubleMaxMp();

public:
	inline int GetNowHp() { return CurrentHp; }
	inline int GetMaxHp() { return BaseStat->MaxHp + EnhancedStat->MaxHp; }

	inline int GetNowMp() { return CurrentMp; }
	inline int GetMaxMp() { return BaseStat->MaxMp + EnhancedStat->MaxMp; }

	inline bool IsDead() { return CurrentHp <= 0; }

	inline int GetAttack() { return BaseStat->Attack + EnhancedStat->Attack; }
	inline int GetDefense() { return BaseStat->Defense + EnhancedStat->Defense; }

	inline const string& GetString() { return Name; }

	inline bool FullHp() { return CurrentHp == GetMaxHp(); }
	inline bool FullMp() { return CurrentMp == GetMaxMp(); }

protected:
	int CurrentHp;
	int CurrentMp;

	string Name;

	Stats* BaseStat;
	Stats* EnhancedStat;

	unordered_map<SkillIdx, Skill> Skills;
};

