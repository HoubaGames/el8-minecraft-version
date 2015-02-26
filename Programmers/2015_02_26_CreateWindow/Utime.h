#ifndef UTOKI_H
#define UTOKI_H

#include <windows.h>
#include <iostream>
#include <fstream>
extern __inline__ uint64_t rdtsc();

class uToki
{
private:
    uint64_t freq[5];//start time
    float koefficient;
//debug variables
    int SotoFile,KakuMay,MaxStep;
    std::fstream logfile;
public:
    uToki();
    float GetMtoki();//in milliseconds
    float GetUtoki();//in milliseconds
    void DebugHajime(int MaxStep,int KakuMay);
};
#endif
