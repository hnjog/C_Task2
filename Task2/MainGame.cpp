#include<iostream>
#include<string>
#include "MainGame.h"
#include "Player.h"
#include "Util.h"
#include "Enums.h"
#include "Skill.h"
#include "Monster.h"
#include "Warrior.h"
#include "Archer.h"
#include "Thief.h"
#include "Magician.h"

MainGame::MainGame()
	:MyPlayer(nullptr)
{
	MyMonster = new Monster(10,100,30,10,10,10,"웨어울프");
	MyMonster->AddSkill(SkillIdx::BaseAttack, { 2.0,0 });
}

MainGame::~MainGame()
{
	SafeDelete(MyPlayer);
	SafeDelete(MyMonster);
}

void MainGame::GameSetting()
{
	string jobs[] = { "전사", "마법사", "도적", "궁수" };
	int job_choice = 0;
	string name;

	cout << "* 이름을 입력해주세요: ";
	cin >> name;

	cout << "<전직 시스템>" << endl;
	cout << name << "님, 환영합니다!" << endl;
	cout << "* 원하시는 직업을 선택해주세요." << endl;

	for (int i = 0; i < 4; i++) {
		cout << (i + 1) << ". " << jobs[i] << endl;
	}

	while (job_choice <= 0 || job_choice > 4)
	{
		cin >> job_choice;
		switch (job_choice) 
		{
		case 1:
			MyPlayer = new Warrior(100, 100, 40, 50, 5, 5, name);
			break;
		case 2:
			MyPlayer = new Magician(50, 200, 30, 40, 6, 6, name);
			break;
		case 3:
			MyPlayer = new Thief(60, 100, 60, 20, 10, 10, name);
			break;
		case 4:
			MyPlayer = new Archer(60, 100, 50, 30, 10, 10, name);
			break;
		default:
			cout << "잘못된 입력입니다." << endl;
			break;
		}
	}

	MyPlayer->AddSkill(SkillIdx::BaseAttack, { 2,50 });
	MyPlayer->AddSkill(SkillIdx::LethalAttack, { 3,0 });

}

void MainGame::PlayGame()
{
	GameSetting();

	cout << "=============================================" << '\n';
	cout << "<스탯 관리 시스템>" << '\n';
	cout << "1. 공격 하기" << '\n';
	cout << "2. 현재 스탯 상태 출력" << '\n';
	cout << "3. 몬스터의 공격" << '\n';
	cout << "4. 나가기" << '\n';

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
			MyPlayer->Attack(MyMonster, SkillIdx::BaseAttack);
			if (MyMonster->IsDead())
			{
				cout << "승리하였습니다!!!" << '\n';
				cout << "당신의 남은 체력 : " << MyPlayer->GetNowHp() << '\n';
				bGameEnd = true;
			}
		}
		break;
		case 2:
		{
			MyPlayer->PrintPlayerStatus();
		}
		break;
		case 3:
		{
			MyMonster->Attack(MyPlayer, SkillIdx::BaseAttack);
			if (MyPlayer->IsDead())
			{
				cout << "패배하였습니다..." << '\n';
				cout << "몬스터의 남은 체력 : " << MyMonster->GetNowHp() << '\n';
				bGameEnd = true;
			}
		}
		break;
		case 4:
		{
			cout << "프로그램을 종료합니다." << '\n';
			bGameEnd = true;
		}
		break;
		default:
			cout << "잘못된 번호를 선택하였습니다. 다시 입력해주세요." << '\n';
			break;
		}
	}

}
