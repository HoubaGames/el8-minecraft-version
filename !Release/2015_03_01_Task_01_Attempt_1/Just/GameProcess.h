#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include "GameMenu.h"
#include <iostream>
//16 bit to type of block
const int chunks=2;
const int repeatblock=8;

struct Chunk
{
    unsigned char Data[65536];
};
class GameProcess:public GameMenu
{
private:
    Chunk Data[chunks*chunks];
    int BlockTex[256];
    Object *Geometry;
public:
    GameProcess();
    ~GameProcess();
    int Escape();
    void Draw();
    void RunCommand(void *Data,int Type);
    void LoadFromFile();
    void ApplyBlock(int x,int y,int z,unsigned char type);
};

#endif // GAMEPROCESS_H
