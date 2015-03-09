#ifndef GAMEMENU_H
#define GAMEMENU_H

//
const int MAX_VERTEX=1024;
const int MAX_FACE=1024;
//

class ProjectGL;
class GameMenu;


struct Object
{
    float vertex[MAX_VERTEX*3];
    float textures[MAX_VERTEX*2];
    float normales[MAX_VERTEX*3];
    int face[MAX_FACE*3];
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
    static int *ExitCallback;//Pointer to continue variable
    GameMenu *Parent;
public:
    void SetProjectGL(ProjectGL*);
    void SetMainPointer(GameMenu**);
    void SetParent(GameMenu*);
    void SetExitCallback(int*);
    virtual int Escape()=0;
    virtual void Draw()=0;
    virtual void RunCommand(void *Data,int Type)=0;
};

#endif // GAMEMENU_H
