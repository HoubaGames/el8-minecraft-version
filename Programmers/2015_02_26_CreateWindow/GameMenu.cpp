#include "GameMenu.h"
#include "ProjectGL.h"

GameMenu::GameMenu()
{
    //ctor
}

void GameMenu::SetProjectGL(ProjectGL *arg)
{
    pGL=arg;
}

void GameMenu::LoadFromFile()
{
    background=pGL->LoadGLTextures("./data/background.bmp");
}
