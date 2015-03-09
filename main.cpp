#include "uTime.h"
#include "ProjectGL.h"
#include "GameMenu.h"
#include "GameMenuRegular.h"
#include "GameProcess.h"
//debug
float tIma,temp;
int tCount;
//window parameters A4 windowed
int ScreenX=1024;
int ScreenY= 724;
bool FullScreen=false;
const float Scale=-1.0;

//System variables
MSG msg;
bool cont;

//Pointers
ProjectGL *pGL;
GameMenu *pGM;//main mune
GameProcess *pGP;//The Game
uTime *uTK;

void OnKeyDown(char key)
{
    if(key==VK_ESCAPE)
	{
        if(pGM->Escape()==1)
            cont=false;
	}
    else
        pGM->RunCommand(&key,1);
}

void OnKeyUp(char key)
{
    pGM->RunCommand(&key,2);
}

void WaitForEvent()
{
    ///* This code shows FPS
    tIma=uTK->GetUtime();
    tCount++;
    while(tIma-temp>1000)
	{
        std::cout<<tCount<<std::endl;
        temp+=1000;
        tCount=0;
	}//*/
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if(msg.message==WM_QUIT)
            cont=false;
	}
}

void SetupMenu()
{
//Create menu
    ((GameMenuRegular*)pGM)->SetTexture("./data/background.bmp");
    ((GameMenuRegular*)pGM)->AddVertex(-1.0f,-1.0f,Scale,0.0f,0.5f,0.0f,0.0f,0.0f);
    ((GameMenuRegular*)pGM)->AddVertex(-1.0f, 1.0f,Scale,0.0f,1.0f,0.0f,0.0f,0.0f);
    ((GameMenuRegular*)pGM)->AddVertex( 1.0f,-1.0f,Scale,0.5f,0.5f,0.0f,0.0f,0.0f);
    ((GameMenuRegular*)pGM)->AddVertex( 1.0f, 1.0f,Scale,0.5f,1.0f,0.0f,0.0f,0.0f);
    ((GameMenuRegular*)pGM)->AddTriangle(0,1,3);
    ((GameMenuRegular*)pGM)->AddTriangle(0,2,3);
//Add element 0
    ((GameMenuRegular*)pGM)->AddElement();
    ((GameMenuRegular*)pGM)->AddVertexElement(0,0,-1.0/3.0,12.0/18.0,Scale, 257.0/512.0,        1.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddVertexElement(0,0, 1.0/3.0,12.0/18.0,Scale, 481.0/512.0,        1.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddVertexElement(0,0,-1.0/3.0, 7.0/18.0,Scale, 257.0/512.0,467.0/512.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddVertexElement(0,0, 1.0/3.0, 7.0/18.0,Scale, 481.0/512.0,467.0/512.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddTriangleElement(0,0,0,1,3);
    ((GameMenuRegular*)pGM)->AddTriangleElement(0,0,0,2,3);
    ((GameMenuRegular*)pGM)->AddVertexElement(0,1,-1.0/3.0,12.0/18.0,Scale, 257.0/512.0,467.0/512.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddVertexElement(0,1, 1.0/3.0,12.0/18.0,Scale, 481.0/512.0,467.0/512.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddVertexElement(0,1,-1.0/3.0, 7.0/18.0,Scale, 257.0/512.0,422.0/512.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddVertexElement(0,1, 1.0/3.0, 7.0/18.0,Scale, 481.0/512.0,422.0/512.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddTriangleElement(0,1,0,1,3);
    ((GameMenuRegular*)pGM)->AddTriangleElement(0,1,0,2,3);
//Submenu element 0
	((GameMenuRegular*)pGM)->SetSubmenu(0,pGP);
//Add element 1
    ((GameMenuRegular*)pGM)->AddElement();
    ((GameMenuRegular*)pGM)->AddVertexElement(1,0,-1.0/3.0, 6.0/18.0,Scale, 257.0/512.0,        1.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddVertexElement(1,0, 1.0/3.0, 6.0/18.0,Scale, 481.0/512.0,        1.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddVertexElement(1,0,-1.0/3.0, 1.0/18.0,Scale, 257.0/512.0,467.0/512.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddVertexElement(1,0, 1.0/3.0, 1.0/18.0,Scale, 481.0/512.0,467.0/512.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddTriangleElement(1,0,0,1,3);
    ((GameMenuRegular*)pGM)->AddTriangleElement(1,0,0,2,3);
    ((GameMenuRegular*)pGM)->AddVertexElement(1,1,-1.0/3.0, 6.0/18.0,Scale, 257.0/512.0,467.0/512.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddVertexElement(1,1, 1.0/3.0, 6.0/18.0,Scale, 481.0/512.0,467.0/512.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddVertexElement(1,1,-1.0/3.0, 1.0/18.0,Scale, 257.0/512.0,422.0/512.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddVertexElement(1,1, 1.0/3.0, 1.0/18.0,Scale, 481.0/512.0,422.0/512.0, 0,0,0);
    ((GameMenuRegular*)pGM)->AddTriangleElement(1,1,0,1,3);
    ((GameMenuRegular*)pGM)->AddTriangleElement(1,1,0,2,3);
//Submenu element 1
	GameMenuRegular *pGMl=new GameMenuRegular;
	((GameMenuRegular*)pGM)->SetSubmenu(1,pGMl);
    ((GameMenuRegular*)pGMl)->SetTexture("./data/background3.bmp");
    ((GameMenuRegular*)pGMl)->AddVertex(-1.0f,-1.0f,Scale,0.0f,0.0f,0.0f,0.0f,0.0f);
    ((GameMenuRegular*)pGMl)->AddVertex(-1.0f, 1.0f,Scale,0.0f,1.0f,0.0f,0.0f,0.0f);
    ((GameMenuRegular*)pGMl)->AddVertex( 1.0f,-1.0f,Scale,1.0f,0.0f,0.0f,0.0f,0.0f);
    ((GameMenuRegular*)pGMl)->AddVertex( 1.0f, 1.0f,Scale,1.0f,1.0f,0.0f,0.0f,0.0f);
    ((GameMenuRegular*)pGMl)->AddTriangle(0,1,3);
    ((GameMenuRegular*)pGMl)->AddTriangle(0,2,3);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
    pGL=new ProjectGL;
    uTK=new uTime;
    pGM=new GameMenuRegular;
    pGP=new GameProcess;
//Set pointers
    pGM->SetProjectGL(pGL);
    pGM->SetMainPointer(&pGM);
    ((GameProcess*)pGP)->SetuTime(uTK);
//Set parametres
    pGL->SetScreenSize(ScreenX,int(float(ScreenX)/1.414),false);
    pGL->SetOnKeyDown(OnKeyDown);
    pGL->SetOnKeyUp(OnKeyUp);
    if(!pGL->CreateGLWindow(hInstance))
        return 1;
	SetupMenu();
    pGM->RunCommand(0,0);//activate
    pGP->SetupDefaultWorld();
//
    tIma=uTK->GetUtime();
    cont=true;
    tCount=0;
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
