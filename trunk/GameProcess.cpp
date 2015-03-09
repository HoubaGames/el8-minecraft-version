#include "GameProcess.h"
#include "ProjectGL.h"
#include <cmath>
///                                     THESE VARIABLES ARE FROM ANOTHER CLASS
//viewer
float StepIKE=0.01;
float StepKKG=0.1;
const float radian=57.295780490442968321226628812406;
float pressed[4][2];
float rotation[2][3];
float position[2][3];
float speed;
float lasttime;
int blocks;

void SetGoVector(int a,float b)
{
	if(a==0)
		speed=b;
	if((a>=1)&&(a<=4))
		rotation[1][a-1]=b;
}

///                                     END

GameProcess::GameProcess()
{
	for(int i=0;i<4;i++)
		for(int j=0;j<2;j++)
			pressed[i][j]=0;
	for(int j=0;j<3;j++)
		rotation[1][j]=position[1][j]=0;
	position[0][0]=2.8;position[0][1]=4;position[0][2]=2.8;
	rotation[0][0]=-45;rotation[0][1]=135;rotation[0][2]=0;
	speed=0;
}

GameProcess::~GameProcess()
{
	//dtor
}
	void GameProcess::SetuTime(uTime *arg)
{
	uTM=arg;
}

void GameProcess::RunCommand(void *Data,int type)
{
	if(type==1)
	{
		char key=*(char*)Data;
		switch(key)
		{
			case 38:pressed[0][1]=StepIKE; break;
			case 40:pressed[0][0]=StepIKE; break;
			case 37:pressed[2][0]=StepKKG;break;
			case 39:pressed[2][1]=StepKKG;break;
			case 'W':pressed[1][0]=StepKKG;break;
			case 'S':pressed[1][1]=StepKKG;break;
			case 'Q':pressed[3][0]=StepKKG;break;
			case 'E':pressed[3][1]=StepKKG;break;
		}
		for(int i=0;i<4;i++)
			SetGoVector(i,pressed[i][1]-pressed[i][0]);
	}
	if(type==2)
	{
		char key=*(char*)Data;
		switch(key)
		{
			case 38:pressed[0][1]=0; break;//VK_UP
			case 40:pressed[0][0]=0; break;//VK_DOWN
			case 37:pressed[2][0]=0;break;//VK_LEFT
			case 39:pressed[2][1]=0;break;//VK_RIGHT
			case 'W':pressed[1][0]=0;break;
			case 'S':pressed[1][1]=0;break;
			case 'Q':pressed[3][0]=0;break;
			case 'E':pressed[3][1]=0;break;
		}
		for(int i=0;i<4;i++)
			SetGoVector(i,pressed[i][1]-pressed[i][0]);
	}
}

int GameProcess::Escape()
{
	if(Parent==NULL)
		return 1;
	*GameMenuActive=Parent;
	return 0;
}

void GameProcess::Draw()
{
//GoTime
	float dt=uTM->GetUtime()-lasttime;
	lasttime+=dt;
	position[1][0]=-speed*sin(rotation[0][1]/radian)*cos(rotation[0][0]/radian);
	position[1][2]=speed*cos(rotation[0][1]/radian)*cos(rotation[0][0]/radian);
	position[1][1]=speed*sin(rotation[0][0]/radian);
	for(int j=0;j<3;j++)
	{
		position[0][j]+=dt*position[1][j];
		rotation[0][j]+=dt*rotation[1][j];
	}
//Draw
	pGL->ClearGLScene();
	pGL->EnableMode(2);
	pGL->CameraRotate(rotation[0][2],0,0,1);
	pGL->CameraRotate(rotation[0][0],1,0,0);
	pGL->CameraRotate(rotation[0][1],0,1,0);
	pGL->CameraMove(position[0][0],position[0][1],position[0][2]);
	for(int dx=0;dx<chunks;dx++)
		for(int dy=0;dy<chunks;dy++)
			pGL->ListExecute(chunks*dx+dy);
	pGL->ShowGLScene();
}

void GameProcess::SetupDefaultWorld()
{
	int value;
	blocks=0;
	float Texture1[2*24]={
		0.0,0.5, 0.5,0.5, 0.0,1.0, 0.5,1.0,
		0.0,0.5, 0.5,0.5, 0.0,1.0, 0.5,1.0,
		0.5,0.5, 1.0,0.5, 0.5,1.0, 1.0,1.0,
		0.5,0.0, 1.0,0.0, 0.5,0.5, 1.0,0.5,
		0.0,1.0, 0.0,0.5, 0.5,0.5, 0.5,1.0,
		0.0,1.0, 0.0,0.5, 0.5,0.5, 0.5,1.0
	},Texture2[48],Texture3[48],Texture4[48];
	float tempVert[3*24]={
		0,0,0, 1,0,0, 1,1,0, 0,1,0,
		0,0,1, 1,0,1, 1,1,1, 0,1,1,
		0,0,1, 1,0,1, 1,0,0, 0,0,0,
		0,1,1, 1,1,1, 1,1,0, 0,1,0,
		0,1,1, 0,0,1, 0,0,0, 0,1,0,
		1,1,0, 1,0,0, 1,0,1, 1,1,1,
	};
	int tempFace[6*6]={
		0,1,2, 0,2,3,
		4,5,6, 4,6,7,
		8,9,10, 8,10,11,
		12,13,14, 12,14,15,
		16,17,18, 16,18,19,
		20,21,22, 20,22,23};
	for(int i=0;i<48;i+=2)
	{
		Texture1[i]/=2;
		Texture1[i+1]/=2;
		Texture2[i]=Texture1[i];
		Texture2[i+1]=Texture1[i+1]+0.5;
		Texture3[i]=Texture1[i]+0.5;
		Texture3[i+1]=Texture1[i+1];
		Texture4[i]=Texture1[i]+0.5;
		Texture4[i+1]=Texture1[i+1]+0.5;
	}
	int step=repeatblock;
	for(int i=0;i<repeatblock;i++)
	for(int j=0;j<repeatblock;j++)
	for(int k=0;k<repeatblock;k++)
		ApplyBlock(i,j,k,0);
	blocks=0;
	for(int i=0;i<repeatblock/2;i++)
	for(int j=0;j<repeatblock/2;j++)
		ApplyBlock(i,i+j,j,1);
	for(int i=repeatblock/2;i<repeatblock;i++)
	for(int j=0;j<repeatblock/2;j++)
		ApplyBlock(i,i+j,j,2);
	for(int i=0;i<repeatblock/2;i++)
	for(int j=repeatblock/2;j<repeatblock;j++)
		ApplyBlock(i,i+j,j,3);
	for(int i=repeatblock/2;i<repeatblock;i++)
	for(int j=repeatblock/2;j<repeatblock;j++)
		ApplyBlock(i,i+j,j,4);
	BlockTex[1]=pGL->LoadGLTextures("./data/Textura.bmp");
	/*BlockTex[1]=pGL->LoadGLTextures("./data/1.bmp");
	BlockTex[2]=pGL->LoadGLTextures("./data/2.bmp");
	BlockTex[3]=pGL->LoadGLTextures("./data/3.bmp");
	BlockTex[4]=pGL->LoadGLTextures("./data/4.bmp");*/
	Geometry=new Object;
	for(int i=0;i<8*24;i++)
		Geometry->vertex[i]=tempVert[i];
	for(int i=0;i<2*24;i++)
		Geometry->textures[i]=Texture1[i];
	for(int i=0;i<2*24;i++)
		Geometry->textures[i+48]=Texture2[i];
	for(int i=0;i<2*24;i++)
		Geometry->textures[i+96]=Texture3[i];
	for(int i=0;i<2*24;i++)
		Geometry->textures[i+144]=Texture4[i];
	for(int i=0;i<6*6;i++)
		Geometry->face[i]=tempFace[i];
	Geometry->facei=36;
	//compile
	for(int dx=0;dx<chunks;dx++)
		for(int dy=0;dy<chunks;dy++)
		{
			CompileChunk(dx,dy);
		}
}
void GameProcess::CompileChunk(int dx,int dy)
{
	int value;
	pGL->ListCompile(chunks*dx+dy);
	pGL->MatrixSave();
	pGL->TextureActivate(BlockTex[1]);
	pGL->CameraMove(dx*16,0,dy*16);
	for(int y=0;y<256;y++)//z axis
		for(int x=0;x<16;x++)//y axis
			for(int z=0;z<16;z++)//x asix
				if((value=Data[chunks*dx+dy].Data[z+16*x+256*y])!=0)
				{
					pGL->MatrixSave();
					pGL->CameraMove(x*1,y*1,z*1);
					pGL->DrawGLScene(Geometry->vertex,(Geometry->textures)+48*--value,0,Geometry->face,Geometry->facei);
					pGL->MatrixLoad();
				}
	pGL->MatrixLoad();
	pGL->ListFinish();
}

void GameProcess::ApplyBlock(int xx,int yy,int zz,unsigned char type)
{
	for(int i=0;i<chunks*chunks;i++)
		for(int y=yy;y<256;y+=repeatblock)
			for(int x=xx;x<16;x+=repeatblock)
				for(int z=zz;z<16;z+=repeatblock)
				{
					Data[i].Data[z+16*x+256*y]=type;
					blocks++;
				}
}
