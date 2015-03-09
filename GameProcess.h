#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include "GameMenu.h"
#include "uTime.h"
#include <iostream>
//16 bit to type of block
const int chunks=8;
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
    uTime *uTM;
private:
	void CompileChunk(int,int);
public:
	void SetuTime(uTime*);
	//
    GameProcess();
    ~GameProcess();
    int Escape();
    void Draw();
    void RunCommand(void *Data,int Type);
    void SetupDefaultWorld();
    void ApplyBlock(int x,int y,int z,unsigned char type);
};

#endif // GAMEPROCESS_H
