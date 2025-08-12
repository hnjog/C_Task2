#pragma once

#include <unordered_map>
#include <string>
#include "Enums.h"
#include "Util.h"

using namespace std;

class Skill;

struct Stats
{
	int MaxHp;
	int MaxMp;
	int Attack;
	int Defense;
	int Accuracy;
	int Speed;

	Stats()
	{
		MaxHp = 0;
		MaxMp = 0;
		Attack = 0;
		Defense = 0;
		Accuracy = 0;
		Speed = 0;
	}

	Stats(int maxHp,int maxMp, int attack, int defense,int accuracy,int speed)
	{
		MaxHp = maxHp;
		MaxMp = maxMp;
		Attack = attack;
		Defense = defense;
		Accuracy = accuracy;
		Speed = speed;
	}

};

class Character
{
public:
	Character();
	Character(int maxHp, int maxMp, int attack, int defense, int accuracy, int speed, string name);
	Character(const Stats& stats, string name);
	virtual ~Character();

	virtual void Attack(Character* Other, SkillIdx skillIdx) = 0;
	virtual void Hit(Character* Hitter, int damage) = 0;

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
	inline int GetAccuracy() { return BaseStat->Accuracy + EnhancedStat->Accuracy; }
	inline int GetSpeed() { return BaseStat->Speed + EnhancedStat->Speed; }

	inline const string& GetString() { return Name; }

	inline bool FullHp() { return CurrentHp == GetMaxHp(); }
	inline bool FullMp() { return CurrentMp == GetMaxMp(); }

public:
	inline void SetName(string& name) { Name = name; }
	inline void SetName(string&& name) { Name = move(name); }

	inline void SetAttackBase(int attack)
	{
		if (IsNotValid(BaseStat) == false)
		{
			BaseStat->Attack = attack;
		}
	}

	inline void SetDefenseBase(int defense)
	{
		if (IsNotValid(BaseStat) == false)
		{
			BaseStat->Defense = defense;
		}
	}

	inline void SetAttackEnhanced(int attack)
	{
		if (IsNotValid(EnhancedStat) == false)
		{
			EnhancedStat->Attack = attack;
		}
	}

	inline void SetDefenseEnhanced(int defense)
	{
		if (IsNotValid(EnhancedStat) == false)
		{
			EnhancedStat->Defense = defense;
		}
	}

	inline void SetAccuracyBase(int accuracy)
	{
		if (IsNotValid(BaseStat) == false)
		{
			BaseStat->Accuracy = accuracy;
		}
	}

	inline void SetSpeedBase(int speed)
	{
		if (IsNotValid(BaseStat) == false)
		{
			BaseStat->Speed = speed;
		}
	}

	inline void SetAccuracyEnhanced(int accuracy)
	{
		if (IsNotValid(EnhancedStat) == false)
		{
			EnhancedStat->Accuracy = accuracy;
		}
	}

	inline void SetSpeedEnhanced(int speed)
	{
		if (IsNotValid(EnhancedStat) == false)
		{
			EnhancedStat->Speed = speed;
		}
	}
	

protected:
	int CurrentHp;
	int CurrentMp;

	string Name;

	Stats* BaseStat;
	Stats* EnhancedStat;

	unordered_map<SkillIdx, Skill> Skills;
};

