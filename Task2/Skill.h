#pragma once

class Skill
{
public:
	Skill();
	Skill(double damageRate, int requireMp);
	virtual ~Skill();

public:
	double DamageRate; // attack 에 곱해질 비율
	int RequireMp;
};