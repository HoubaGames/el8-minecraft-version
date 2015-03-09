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
    int Activate();
    int Activate(int);
    void SelectItem(int);
//setup
	void SetTexture(char *FromFile);
    void AddVertex(float vx,float vy,float vz,float tx,float ty,float nx,float ny,float nz);
    void AddTriangle(int a1,int a2,int a3);
    void AddElement();
    void AddVertexElement(int element,int mode,float vx,float vy,float vz,float tx,float ty,float nx,float ny,float nz);
    void AddTriangleElement(int element,int mode,int a1,int a2,int a3);
    void SetSubmenu(int element,GameMenu* SubMenu);
//
    int Escape();
    void Draw();
    void RunCommand(void *Data,int Type);
};

#endif // GAMEMENUREGULAR_H
