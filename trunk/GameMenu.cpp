#include <iostream>
#include "GameMenu.h"
#include "ProjectGL.h"

ProjectGL* GameMenu::pGL;
GameMenu** GameMenu::GameMenuActive;
int* GameMenu::ExitCallback;

void GameMenu::SetProjectGL(ProjectGL *arg)
{
    pGL=arg;
}

void GameMenu::SetMainPointer(GameMenu** arg)
{
    GameMenuActive=arg;
}

void GameMenu::SetParent(GameMenu *arg)
{
    Parent=arg;
}

int GameMenu::Escape()
{
    if(Parent)
	{
        *GameMenuActive=Parent;
        return 0;
	}
    return 1;
}
//
