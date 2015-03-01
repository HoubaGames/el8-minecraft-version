#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <iostream>

#include "uTime.h"

class ProjectGL;
class GameMenu;


struct Object
{
    float vertex[1024*8];
    int face[1024*3];
    int facei,facef;
};

class Element
{
public:
    Object *Data;
    GameMenu *ToOpen;
};
class GameMenu
{
protected:
    static ProjectGL *pGL;
    static GameMenu **GameMenuActive;//Pointer to pointer in Main
    static uTime *uTM;
    GameMenu *Parent;
public:
    GameMenu();
    void SetProjectGL(ProjectGL*);
    void SetMainPointer(GameMenu**);
    void SetParent(GameMenu*);
    void SetuTime(uTime*);
    virtual int Escape();
    virtual void Draw();
    virtual void RunCommand(void *Data,int Type);
};

#endif // GAMEMENU_H
