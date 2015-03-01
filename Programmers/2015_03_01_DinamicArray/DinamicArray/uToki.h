#ifndef UTOKI_H
#define UTOKI_H

#include <windows.h>
#include <iostream>
///link -winmm

class uToki
{
private:
    uint64_t datai[5];
    float dataf;
public:
    uToki();
    float GetUtoki();//in milliseconds
};
#endif
