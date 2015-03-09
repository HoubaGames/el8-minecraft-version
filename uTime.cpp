#include "uTime.h"

uTime::uTime()
{
    QueryPerformanceCounter((LARGE_INTEGER*)(datai));
    QueryPerformanceFrequency((LARGE_INTEGER*)(datai+1));
    dataf=1000.0/float(datai[1]);
}

float uTime::GetUtime()
{
    QueryPerformanceCounter((LARGE_INTEGER*)(datai+1));
    return float(datai[1]-datai[0])*dataf;
}
