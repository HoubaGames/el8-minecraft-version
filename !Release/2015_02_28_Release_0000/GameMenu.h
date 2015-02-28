#ifndef GAMEMENU_H
#define GAMEMENU_H

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
static ProjectGL *pGL;
static GameMenu **GameMenuActive;//Pointer to pointer in Main
private:
    int background;//texture
    int Elemi;//Number of elements
    int ActiveItem;
    Element *Elem[256];
    Object *Data;
    GameMenu *Parent;
public:
    GameMenu();
    void SetProjectGL(ProjectGL*);
    void SetMainPointer(GameMenu**);
    void LoadFromFile();
    int Activate();
    int Activate(int);
    void SelectItem(int);
    int Escape();
    void Draw();
};

#endif // GAMEMENU_H
