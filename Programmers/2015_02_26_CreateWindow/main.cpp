#include "utime.h"
#include "ProjectGL.h"

//debug
float tIma,temp;
int tCount;
//window parameters
int ScreenX=1024;
//
MSG msg;
bool cont;

//technical parameters
ProjectGL *pGL;
GameMenu *pGM;
uToki *uTK;

void OnKeyDown(char key)
{
    switch(key){
        case VK_ESCAPE:cont=false;break;
    }
}

void OnKeyUp(char key)
{
}

void WaitForEvent()
{
    tIma=uTK->GetUtoki();
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
    uTK=new uToki;
    pGM=new GameMenu;
//Set pointers
    pGM->SetProjectGL(pGL);
    pGL->SetGameMenu(pGM);
//Set parametres
    pGM->LoadFromFile();
    pGL->SetScreenSize(ScreenX,int(float(ScreenX)/1.414),false);
    pGL->SetOnKeyDown(OnKeyDown);
    pGL->SetOnKeyUp(OnKeyUp);

    if(!pGL->CreateGLWindow(hInstance))
        return 1;

    tIma=uTK->GetUtoki();
    cont=true;
    tCount=0;
    while(cont){
        WaitForEvent();
        pGL->DrawGLScene();}
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
