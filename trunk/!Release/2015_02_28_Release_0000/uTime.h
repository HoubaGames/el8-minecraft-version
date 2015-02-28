#ifndef UTIME_H
#define UTIME_H

#include <windows.h>
#include <iostream>//uint64_t

class uTime
{
private:
    uint64_t datai[5];//start time
    float dataf;
public:
    uTime();
    float GetUtime();//in milliseconds
};
#endif
