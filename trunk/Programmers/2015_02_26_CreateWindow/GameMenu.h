#ifndef GAMEMENU_H
#define GAMEMENU_H

class ProjectGL;

class GameMenu
{
private:
    ProjectGL *pGL;
public:
    int background;
public:
    GameMenu();
    void SetProjectGL(ProjectGL*);
    void LoadFromFile();
};

#endif // GAMEMENU_H
