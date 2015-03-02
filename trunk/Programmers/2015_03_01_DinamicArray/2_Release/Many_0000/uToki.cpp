#include "uToki.h"

uToki::uToki()
{
    QueryPerformanceCounter((LARGE_INTEGER*)(datai));
    QueryPerformanceFrequency((LARGE_INTEGER*)(datai+1));
    dataf=1000.0/float(datai[1]);
}

float uToki::GetUtoki()
{
    QueryPerformanceCounter((LARGE_INTEGER*)(datai+1));
    return float(datai[1]-datai[0])*dataf;
}
