#include "Ooi.h"
#include "uTime.h"

#include <iostream>

int main()
{
    Ooi my;
    uTime utm;
    float ima=utm.GetUtime();
    uint64_t i,d=1;
    for(i=0;i<-1;i+=d){
        if((utm.GetUtime()-ima)>1000){
            std::cout<<"    "<<float(i)/1000000<<std::endl;
            ima+=1000;
        }
        if(!my.IndexDeInsert(i,i))
            break;}
    std::cout<<std::endl;
    for(uint64_t j=d;j<10*d+1;j+=d)
        std::cout<<my.IndexDeYomu(i-j)<<std::endl;
}
