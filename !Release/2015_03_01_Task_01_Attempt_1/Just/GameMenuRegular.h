#ifndef GAMEMENUREGULAR_H
#define GAMEMENUREGULAR_H

#include "GameMenu.h"
#include <iostream>

class GameMenuRegular:public GameMenu
{
private:
    int background;//texture
    int Elemi;//Number of elements
    int ActiveItem;
    Element *Elem[256];
    Object *Data;
public:
    GameMenuRegular();
    void LoadFromFile(GameMenu*);
    int Activate();
    int Activate(int);
    void SelectItem(int);
//
    int Escape();
    void Draw();
    void RunCommand(void *Data,int Type);
};

#endif // GAMEMENUREGULAR_H
