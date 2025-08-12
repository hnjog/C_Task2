#include"Inventory.h"
#include"Character.h"
#include"Util.h"
#include <iostream>

Inventory::Inventory(Character* owner)
	:Owner(owner)
{
	ItemMap.reserve(static_cast<size_t>(ItemIdx::ItemMax));
}

Inventory::~Inventory()
{
	ItemMap.clear();
	Owner = nullptr;
}

void Inventory::AddItem(ItemIdx itemIdx, int count)
{
	if (itemIdx >= ItemIdx::ItemMax)
	{
		return;
	}

	if (count <= 0)
	{
		return;
	}

	// 효과 매핑 임시 (DataTable이 필요하지만 임시로 itemidx = effectIdx 적용)
	if (ItemMap.find(itemIdx) == ItemMap.end())
	{
		ItemMap.insert(make_pair(itemIdx, Item{ count,static_cast<EffectIdx>(itemIdx) }));
	}
	else
	{
		ItemMap[itemIdx].ItemCount += count;
	}
}

bool Inventory::UseItem(ItemIdx itemIdx, Character* Target)
{
	if (itemIdx >= ItemIdx::ItemMax)
	{
		return false;
	}

	if (IsNotValid(Target))
	{
		return false;
	}

	// 없는 아이템
	if (ItemMap.find(itemIdx) == ItemMap.end())
	{
		return false;
	}

	// 개수가 모자라다
	if (ItemMap[itemIdx].ItemCount <= 0)
	{
		return false;
	}
	
	bool result = Effect(ItemMap[itemIdx].Effect, Target);
	
	if (result)
	{
		// 사용 성공
		ItemMap[itemIdx].ItemCount--;
	}

	return result;
}

int Inventory::GetItemCount(ItemIdx itemIdx)
{
	if (itemIdx >= ItemIdx::ItemMax)
	{
		return 0;
	}

	return ItemMap[itemIdx].ItemCount;
}

bool Inventory::Effect(EffectIdx effectIdx, Character* Target)
{
	// 원래는 enum 등으로 실패 원인을 반환하는 것이 정석이지만 임시용 bool
	if (effectIdx >= EffectIdx::EffectMax)
	{
		return false;
	}

	if (IsNotValid(Target))
	{
		return false;
	}

	// 이 방식은 현재 effect 개수 등이 많지 않기에 사용
	// 차후 effect가 늘어날수록 해당 방식은 개선되어야 하며
	// effect map 등을 이용하여 별도의 effect class 구현이 나을듯 하다
	switch (effectIdx)
	{
	case HealHp:
	{
		if (Target->FullHp())
			return false;

		// 해당 수치는 ItemBase 클래스와 DataTable 연동이 나을듯하다
		Target->HealHp(20);
		cout << "HP 포션이 1개 차감됩니다" << '\n';
	}
		break;
	case ManaRefrain:
	{
		if (Target->FullMp())
			return false;

		Target->RefreshMp(20);
		cout << "MP 포션이 1개 차감됩니다" << '\n';
	}
		break;
	}

	return true;
}
