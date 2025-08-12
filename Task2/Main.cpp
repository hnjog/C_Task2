#include <iostream>
#include "MainGame.h"

int main()
{
    MainGame* mainGame = new MainGame();
    mainGame->PlayGame();
    delete mainGame;
}