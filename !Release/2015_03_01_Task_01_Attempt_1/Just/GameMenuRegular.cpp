#include "GameMenuRegular.h"
#include "projectgl.h"


GameMenuRegular::GameMenuRegular()
{
    Data=new Object;
    Elemi=0;
    Parent=NULL;
    ActiveItem=-1;
}

void GameMenuRegular::LoadFromFile(GameMenu* pGP)
{
//Create Demo smt
    background=pGL->LoadGLTextures("./data/background.bmp");
    float dep=-1.0;
    float tempVert[32]={
        -1,-1,dep, 0,0.5, 0,0,0,
        -1,1,dep, 0,1, 0,0,0,
        1,-1,dep, 0.5,0.5, 0,0,0,
        1,1,dep, 0.5,1, 0,0,0};
    int tempFace[6]={0,1,3, 0,2,3};
    for(int i=0;i<32;i++)
        Data->vertex[i]=tempVert[i];
    for(int i=0;i<6;i++)
        Data->face[i]=tempFace[i];
    Data->facei=6;
    Data->facef=32;
//Add element
    float tempVert2[32]={
        -1.0/3.0,12.0/18.0,dep,         0.5,        1.0, 0,0,0,
         1.0/3.0,12.0/18.0,dep, 481.0/512.0,        1.0, 0,0,0,
        -1.0/3.0, 7.0/18.0,dep,         0.5,467.0/512.0, 0,0,0,
         1.0/3.0, 7.0/18.0,dep, 481.0/512.0,467.0/512.0, 0,0,0};
    Elem[Elemi]=new Element;
    Elem[Elemi]->Data=new Object[2];
    for(int i=0;i<32;i++)
        Elem[Elemi]->Data[0].vertex[i]=tempVert2[i];
    for(int i=0;i<6;i++)
        Elem[Elemi]->Data[0].face[i]=tempFace[i];
    for(int i=0;i<32;i+=8){
        tempVert2[i+3]+=0;//TexShiftX
        tempVert2[i+4]-=45.0/512.0;}//TexShiftY
    for(int i=0;i<32;i++)
        Elem[Elemi]->Data[1].vertex[i]=tempVert2[i];
    for(int i=0;i<6;i++)
        Elem[Elemi]->Data[1].face[i]=tempFace[i];
    Elem[Elemi]->Data[0].facei=6;
    Elem[Elemi]->Data[1].facei=6;
// Add submenu
    Elem[Elemi]->ToOpen=pGP;
    pGP->SetParent(this);
    Elemi++;
//Another
    float tempVert3[32]={
        -1.0/3.0,6.0/18.0,dep,         0.5,        1.0, 0,0,0,
         1.0/3.0,6.0/18.0,dep, 481.0/512.0,        1.0, 0,0,0,
        -1.0/3.0,1.0/18.0,dep,         0.5,467.0/512.0, 0,0,0,
         1.0/3.0,1.0/18.0,dep, 481.0/512.0,467.0/512.0, 0,0,0};
    Elem[Elemi]=new Element;
    Elem[Elemi]->Data=new Object[2];
    tempVert[4]=0;
    tempVert[19]*=2;
    tempVert[20]=0;
    tempVert[27]*=2;
    for(int i=0;i<32;i++)
        Elem[Elemi]->Data[0].vertex[i]=tempVert3[i];
    for(int i=0;i<6;i++)
        Elem[Elemi]->Data[0].face[i]=tempFace[i];
    for(int i=0;i<32;i+=8){
        tempVert3[i+3]+=0;//TexShiftX
        tempVert3[i+4]-=45.0/512.0;}//TexShiftY
    for(int i=0;i<32;i++)
        Elem[Elemi]->Data[1].vertex[i]=tempVert3[i];
    for(int i=0;i<6;i++)
        Elem[Elemi]->Data[1].face[i]=tempFace[i];
    Elem[Elemi]->Data[0].facei=6;
    Elem[Elemi]->Data[1].facei=6;
//
    GameMenuRegular *temp3=new GameMenuRegular();
    Elem[Elemi]->ToOpen=temp3;
    temp3->background=pGL->LoadGLTextures("./data/Background3.bmp");
    temp3->SetParent(this);
    for(int i=0;i<32;i++)
        temp3->Data->vertex[i]=tempVert[i];
    for(int i=0;i<6;i++)
        temp3->Data->face[i]=tempFace[i];
    temp3->Data->facei=6;
    temp3->Data->facef=32;
    Elemi++;
//
}

//glEnable(GL_DEPTH_TEST);
//virtual
void GameMenuRegular::Draw()
{
    int temp;
    pGL->ClearGLScene();
    pGL->EnableMode(1);
    pGL->DrawGLScene(Data->vertex,Data->face,Data->facei,background,0);
    for(int i=0;i<Elemi;i++){
        temp=(i==ActiveItem)?1:0;
        pGL->DrawGLScene(Elem[i]->Data[temp].vertex,Elem[i]->Data[temp].face,Elem[i]->Data[temp].facei,-1,2);}
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
    if(type==5){
        LoadFromFile((GameMenu*)Data);}else{
    if(type==6)
        Activate();
    }}
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
