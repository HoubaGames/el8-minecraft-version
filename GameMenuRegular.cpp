#include "GameMenuRegular.h"
#include "projectgl.h"


GameMenuRegular::GameMenuRegular()
{
    Data=new Object;
    Data->facef=0;
    Data->facei=0;
    Elemi=0;
    Parent=NULL;
    ActiveItem=-1;
}

void GameMenuRegular::SetTexture(char *FromFile)
{
    background=pGL->LoadGLTextures(FromFile);
}

void GameMenuRegular:: AddVertex(float vx,float vy,float vz,float tx,float ty,float nx,float ny,float nz)
{
	int facef=Data->facef;
    Data->vertex[facef*3+0]=vx;
    Data->vertex[facef*3+1]=vy;
    Data->vertex[facef*3+2]=vz;
    Data->textures[facef*2+0]=tx;
    Data->textures[facef*2+1]=ty;
    Data->normales[facef*3+0]=nx;
    Data->normales[facef*3+1]=ny;
    Data->normales[facef*3+2]=nz;
    Data->facef++;
}

void GameMenuRegular::AddTriangle(int a1,int a2,int a3)
{
	Data->face[Data->facei++]=a1;
	Data->face[Data->facei++]=a2;
	Data->face[Data->facei++]=a3;
}

void GameMenuRegular::AddElement()
{
    Elem[Elemi]=new Element;
    Elem[Elemi]->Data=new Object[2];
    Elem[Elemi]->Data[0].facef=0;
    Elem[Elemi]->Data[0].facei=0;
    Elem[Elemi]->Data[1].facef=0;
    Elem[Elemi]->Data[1].facei=0;
    Elemi++;
}
void GameMenuRegular::AddVertexElement(int element,int mode,float vx,float vy,float vz,float tx,float ty,float nx,float ny,float nz)
{
	int facef=Elem[element]->Data[mode].facef;
    Elem[element]->Data[mode].vertex[facef*3+0]=vx;
    Elem[element]->Data[mode].vertex[facef*3+1]=vy;
    Elem[element]->Data[mode].vertex[facef*3+2]=vz;
    Elem[element]->Data[mode].textures[facef*2+0]=tx;
    Elem[element]->Data[mode].textures[facef*2+1]=ty;
    Elem[element]->Data[mode].normales[facef*3+0]=nx;
    Elem[element]->Data[mode].normales[facef*3+1]=ny;
    Elem[element]->Data[mode].normales[facef*3+2]=nz;
    Elem[element]->Data[mode].facef++;
}

void GameMenuRegular::AddTriangleElement(int element, int mode,int a1,int a2,int a3)
{
	 Elem[element]->Data[mode].face[Elem[element]->Data[mode].facei++]=a1;
	 Elem[element]->Data[mode].face[Elem[element]->Data[mode].facei++]=a2;
	 Elem[element]->Data[mode].face[Elem[element]->Data[mode].facei++]=a3;
}

void GameMenuRegular::SetSubmenu(int element, GameMenu *sub)
{
    Elem[element]->ToOpen=sub;
    sub->SetParent(this);
}

//glEnable(GL_DEPTH_TEST);
//virtual
void GameMenuRegular::Draw()
{
    int temp;
    pGL->ClearGLScene();
    pGL->EnableMode(1);
    pGL->TextureActivate(background);
    pGL->DrawGLScene(Data->vertex,Data->textures,0,Data->face,Data->facei);
    for(int i=0;i<Elemi;i++){
        temp=(i==ActiveItem)?1:0;
        pGL->DrawGLScene(Elem[i]->Data[temp].vertex,Elem[i]->Data[temp].textures,0,Elem[i]->Data[temp].face,Elem[i]->Data[temp].facei);}
    pGL->ShowGLScene();
}

int GameMenuRegular::Escape()
{
    if(ActiveItem<0)
        return Activate(-2);
    ActiveItem=-1;
    return 0;
}

void GameMenuRegular::RunCommand(void *Data,int type)
{
    if(type==1){
//press button
        char key=((char*)Data)[0];
        if((key>='0')&&(key<='9')){
            SelectItem(key-'0');}else{
        if(key==VK_RETURN){
            Activate(-1);
        }}}else{
    if(type==6)
        Activate();
    }
}
//
void GameMenuRegular::SelectItem(int arg)
{
    ActiveItem=arg;
}

int GameMenuRegular::Activate()
{
    *GameMenuActive=this;
}

int GameMenuRegular::Activate(int arg)
{
    if(arg==-1){
        if((ActiveItem<0)||(Elemi<=ActiveItem))
            return 1;
        if(Elem[ActiveItem]->ToOpen==NULL)
            return 1;
        *GameMenuActive=Elem[ActiveItem]->ToOpen;
        return 0;}
    if(arg<-1){
        if(Parent==NULL)
            return 1;
        *GameMenuActive=Parent;
        return 0;}
    if(arg>=Elemi)
        return 1;
    *GameMenuActive=Elem[arg]->ToOpen;
    return 0;
}

//
