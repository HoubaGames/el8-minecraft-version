#ifndef PROJECTGL_H
#define PROJECTGL_H

#include <windows.h>		// Заголовочный файл для Windows
#include <iostream>
#include <fstream>
#include <gl\gl.h>			// Заголовочный файл для OpenGL32 библиотеки
#include <gl\glaux.h>		// Load texture
//#include <gl\glext.h>

const float WindowFogDensity=0.003;
const float WindowDepth=10000;
const float WindowAngle=1024;
const float WindowNear=0.1;

LRESULT CALLBACK NWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

class ProjectGL
{
private:
//
    bool created;
    GLuint TexturaWoLoaded[1024][1];
    GLuint TexturaWoLoadedc;
    PIXELFORMATDESCRIPTOR pfd;//WndProc
    HWND hWnd;
    HGLRC hRC;
    HDC hDC;
    bool keys[256];//Keyoard
 //window settings
    int WinX,WinY;
    float InitX,InitY;
    float WinAsp;
    int WinFlag;
    bool fullscreen;
    void (*FOnKeyDown)(char);
    void (*FOnKeyUp)(char);
//
private:
    void InitGL();
    void ReSizeGLScene();
    GLuint DisplayList;
public:
    ProjectGL();
    ~ProjectGL();
    bool CreateGLWindow(HINSTANCE);
    bool DeleteGLWindow();
    LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
//set window params
    //void SetGameMenu(GameMenu*);
    void SetOnKeyDown(void(*OnKeyPress)(char key));
    void SetOnKeyUp(void(*OnKeyPress)(char key));
    void SetScreenSize(int ScreenX,int ScreenY,bool FullScreen=false);
//Drawing
    void MatrixSave();
    void MatrixLoad();
    void ListCompile(int number);
    void ListFinish();
    void EnableMode(char translateKey);
    void ClearGLScene();
    void CameraMove(float x,float y,float z);
    void CameraRotate(float angle,float x,float y,float z);
    int DrawGLScene(float *vertex,float *text, float *normal,int *face,int facei,int texture=-1,char key=0);/* comment */
    void ShowGLScene();
//
    int LoadGLTextures(char* file);
    bool GetKeys(unsigned char key);
};


/*
EnableMode
1 - Scale to window coordinates are -1 to 1 , -1 to 1 , -1
DrawGLScene: translatekey to:
2 - to draw by current texture
*/
#endif // PROJECTGL_H
