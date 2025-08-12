#include"Skill.h"

Skill::Skill()
	:Skill(0, 0)
{
}

Skill::Skill(double damageRate, int requireMp)
	:DamageRate(damageRate),
	RequireMp(requireMp)
{
}

Skill::~Skill()
{
}
