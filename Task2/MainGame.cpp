#include "MainGame.h"
#include "Player.h"
#include "Util.h"
#include<iostream>
#include<string>
#include "Enums.h"
#include "Skill.h"

MainGame::MainGame()
	:MyPlayer(nullptr)
{
	tester = new Character(1000,1000,40,0,"Tester");
	tester->AddSkill(SkillIdx::BaseAttack, { 2.0,0 });
}

MainGame::~MainGame()
{
	SafeDelete(MyPlayer);
	SafeDelete(tester);
}

void MainGame::GameSetting()
{
	int hp = 0, mp = 0;
	while (hp < 60 || mp < 60)
	{
		cout << "HP와 MP를 입력해주세요:";
		cin >> hp >> mp;
		if (hp < 60 || mp < 60)
		{
			cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요." << '\n';
		}
	}

	int attack = 0, defense = 0;
	while (attack < 30 || defense < 30)
	{
		cout << "공격력과 방어력을 입력해주세요:";
		cin >> attack >> defense;
		if (attack < 30 || defense < 30)
		{
			cout << "공격력이나 방어력의 값이 너무 작습니다. 다시 입력해주세요." << '\n';
		}
	}

	
	cout << "마지막으로 이름을 입력해주세요:";
	string name;
	cin >> name;
	MyPlayer = new Player(hp, mp, attack, defense, name);

	MyPlayer->AddSkill(SkillIdx::BaseAttack, { 2,50 });
	MyPlayer->AddSkill(SkillIdx::LethalAttack, { 3,0 });

	MyPlayer->GetItem(ItemIdx::HealthPotion, 5);
	MyPlayer->GetItem(ItemIdx::ManaPotion, 5);
	cout << "* 포션이 지급되었습니다. (HP, MP 포션 각 5개)" << '\n';
	cout << "* 운영자의 변덕으로 체력과 MP가 절반으로 시작됩니다!" << '\n';
	MyPlayer->HalfHp();
	MyPlayer->HalfMp();
	cout << "현재 HP, MP : " << MyPlayer->GetNowHp() << ", " << MyPlayer->GetNowMp() << '\n';
}

void MainGame::PlayGame()
{
	GameSetting();

	cout << "=============================================" << '\n';
	cout << "<스탯 관리 시스템>" << '\n';
	cout << "1. HP 회복" << '\n';
	cout << "2. MP 회복" << '\n';
	cout << "3. HP 강화" << '\n';
	cout << "4. MP 강화" << '\n';
	cout << "5. 공격 스킬 사용" << '\n';
	cout << "6. 필살기 사용" << '\n';
	cout << "7. 나가기" << '\n';
	cout << "8. 테스터의 공격" << '\n';

	int num = 0;
	bool bGameEnd = false;
	while (bGameEnd == false)
	{
		cout << "번호를 선택해주세요:";
		cin >> num;

		switch (num)
		{
		case 1:
		{
			if (MyPlayer->GetItemCount(ItemIdx::HealthPotion) <= 0)
			{
				cout << "포션이 부족합니다" << '\n';
			}
			else if(MyPlayer->FullHp() == false)
			{
				MyPlayer->UseItem(ItemIdx::HealthPotion);
				cout << "현재 HP : " << MyPlayer->GetNowHp() << '\n';
				cout << "남은 HP 포션 수 : " << MyPlayer->GetItemCount(ItemIdx::HealthPotion) << '\n';
			}
			else
			{
				cout << "HP가 가득차있습니다!"<< '\n';
				cout << "현재 HP : " << MyPlayer->GetNowHp() << '\n';
			}
		}
		break;
		case 2:
		{
			if (MyPlayer->GetItemCount(ItemIdx::ManaPotion) <= 0)
			{
				cout << "포션이 부족합니다" << '\n';
			}
			else if(MyPlayer->FullMp() == false)
			{
				MyPlayer->UseItem(ItemIdx::ManaPotion);
				cout << "현재 MP : " << MyPlayer->GetNowMp() << '\n';
				cout << "남은 MP 포션 수 : " << MyPlayer->GetItemCount(ItemIdx::ManaPotion) << '\n';
			}
			else
			{
				cout << "MP가 가득차있습니다!" << '\n';
				cout << "현재 MP : " << MyPlayer->GetNowMp() << '\n';
			}
		}
		break;
		case 3:
		{
			MyPlayer->BoostDoubleMaxHp();
			cout << "현재 HP : " << MyPlayer->GetNowHp() << '\n';
		}
		break;
		case 4:
		{
			MyPlayer->BoostDoubleMaxMp();
			cout << "현재 MP : " << MyPlayer->GetNowMp() << '\n';
		}
		break;
		case 5:
		{
			MyPlayer->Attack(tester, SkillIdx::BaseAttack);
		}
		break;
		case 6:
		{
			MyPlayer->Attack(tester, SkillIdx::LethalAttack);
		}
		break;
		case 7:
		{
			cout << "프로그램을 종료합니다." << '\n';
			bGameEnd = true;
		}
		break;
		case 8:
		{
			tester->Attack(MyPlayer, SkillIdx::BaseAttack);
			cout << "Tester가 당신을 떼립니다!" << '\n';
			cout << "당신의 HP : " << MyPlayer->GetNowHp() << '\n';
		}
		break;
		default:
			cout << "잘못된 번호를 선택하였습니다. 다시 입력해주세요." << '\n';
			break;
		}
	}

}
