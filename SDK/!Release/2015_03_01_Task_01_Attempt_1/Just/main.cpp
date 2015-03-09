#include "utime.h"
#include "ProjectGL.h"
#include "GameMenuRegular.h"
#include "GameProcess.h"
//debug
float tIma,temp;
int tCount;
//window parameters
int ScreenX=1024;
//
MSG msg;
bool cont;

//Pointers
ProjectGL *pGL;
GameMenu *pGM;
uTime *uTK;

void OnKeyDown(char key)
{
    void *arg=&key;
    if(key==VK_ESCAPE){
        if(pGM->Escape()==1)
            cont=false;}
    else
        pGM->RunCommand(&key,1);
}

void OnKeyUp(char key)
{
    void *arg=&key;
    pGM->RunCommand(&key,2);
}

void WaitForEvent()
{
    tIma=uTK->GetUtime();
    tCount++;
    while(tIma-temp>1000){
        std::cout<<tCount<<std::endl;
        temp+=1000;
        tCount=0;}
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if(msg.message==WM_QUIT)
            cont=false;}
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
    pGL=new ProjectGL;
    uTK=new uTime;
    pGM=new GameMenuRegular;
    GameProcess *pGP=new GameProcess;
//Set pointers
    pGM->SetProjectGL(pGL);
    pGM->SetMainPointer(&pGM);
    pGM->SetuTime(uTK);
    //pGL->SetGameMenu(pGM);
//Set parametres
    pGL->SetScreenSize(ScreenX,int(float(ScreenX)/1.414),false);
    pGL->SetOnKeyDown(OnKeyDown);
    pGL->SetOnKeyUp(OnKeyUp);
    if(!pGL->CreateGLWindow(hInstance))
        return 1;
    pGM->RunCommand(pGP,5);//load from file
    tIma=uTK->GetUtime();
    cont=true;
    tCount=0;
    pGM->RunCommand(0,0);//activate
    pGP->LoadFromFile();
    while(cont){
        WaitForEvent();
        pGM->Draw();}
    pGL->DeleteGLWindow();
    return 0;//*/
}
///////////////// On Event
/*
void OnMouseMove(int x,int y)
{
    float dx=float(x)/float(WinX)-0.5;
    float dy=float(2*y-WinY)/2/float(WinX);
}*/
///////////////////////////////////////////////// CLASS SCENE
