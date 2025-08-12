#pragma once

class MainGame
{
public:
	MainGame();
	virtual ~MainGame();

public:
	void PlayGame();

protected:

	void GameSetting();
protected:
	class Player* MyPlayer;
	class Character* tester;
};

