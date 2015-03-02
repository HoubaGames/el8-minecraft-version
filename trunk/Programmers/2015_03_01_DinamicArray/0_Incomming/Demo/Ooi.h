
#include <windows.h>
#include <iostream>
const int depth=15;
const int SLice=2;
class Ooi
{
private:
    int *Data[depth];
    uint64_t counter;
    uint64_t WaitingFor;
    int WaitingI;
public:
    Ooi();
    bool AppEnd(int arg);
    bool IndexDeInsert(int arg,uint64_t Index);
    int IndexDeYomu(uint64_t Index);
};

Ooi::Ooi()
{
    counter=0;
    WaitingFor=1;
    WaitingI=1;
    for(int i=1;i<depth;i++)
        Data[i]=NULL;
    Data[0]=new int[1];
};
bool Ooi::AppEnd(int arg)
{
    return IndexDeInsert(arg,counter++);
}
bool Ooi::IndexDeInsert(int arg, uint64_t index)
{
    uint64_t d=1,i,mult;
    counter=(counter<index)?index:counter;
    while(index>=WaitingFor){
            std::cout<<WaitingFor<<std::endl;
        if(depth<=WaitingI)
            return false;
        for(i=0,mult=1;i<WaitingI;i++)
            mult=mult<<SLice;
        Data[WaitingI]=new int[mult];
        WaitingFor+=mult;
        WaitingI++;}
    for(i=0;index>=d;i++,d=d<<SLice){
        index-=d;}
    Data[i][index]=arg;
    return true;
}
int Ooi::IndexDeYomu(uint64_t index)
{
    uint64_t d=1,i;
    for(i=0;index>=d;i++,d=d<<SLice)
        index-=d;
    return Data[i][index];
}
