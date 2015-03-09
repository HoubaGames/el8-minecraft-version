#include "GameMenu.h"
#include "ProjectGL.h"
ProjectGL* GameMenu::pGL;
GameMenu** GameMenu::GameMenuActive;
uTime* GameMenu::uTM;

GameMenu::GameMenu()
{
    Parent=NULL;
}
void GameMenu::SetProjectGL(ProjectGL *arg)
{
    pGL=arg;
}

void GameMenu::SetMainPointer(GameMenu** arg)
{
    GameMenuActive=arg;
}

void GameMenu::SetuTime(uTime* arg)
{
    uTM=arg;
}

void GameMenu::SetParent(GameMenu *arg)
{
    Parent=arg;
}
void GameMenu::RunCommand(void *Data,int Type)
{
    std::cout<<"a"<<std::endl;
}

void GameMenu::Draw()
{
    std::cout<<"a"<<std::endl;
}

int GameMenu::Escape()
{
    if(Parent){
        *GameMenuActive=Parent;
        return 0;}
    return 1;
}
//
