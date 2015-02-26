#include "utime.h"

extern __inline__ uint64_t rdtsc()
{
    uint64_t x;
    asm volatile ("rdtsc":"=A"(x));
    return x;
}

uToki::uToki()
{
    SotoFile=1;MaxStep=0;KakuMay=0;
    uint64_t chit=timeGetTime();while(timeGetTime()==chit){}
    QueryPerformanceCounter((LARGE_INTEGER*)(freq+1));
    freq[2]=chit+1;
    QueryPerformanceFrequency((LARGE_INTEGER*)freq);
    koefficient=1000.0/freq[0];
}

float uToki::GetUtoki()
{
    QueryPerformanceCounter((LARGE_INTEGER*)(freq+3));
    return float(freq[3]-freq[1])*koefficient;
}

float uToki::GetMtoki()
{
    freq[4]=timeGetTime();
    return float(freq[4]-freq[2]);
}

void uToki::DebugHajime(int a,int b)
{
    MaxStep=a;KakuMay=b;
    SotoFile=0;
}
