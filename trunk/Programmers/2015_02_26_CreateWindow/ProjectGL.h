
#ifndef PROJECTGL_H
#define PROJECTGL_H

#include <windows.h>		// Заголовочный файл для Windows
#include <iostream>
#include <fstream>
#include <gl\gl.h>			// Заголовочный файл для OpenGL32 библиотеки
#include <gl\glu.h>			// Заголовочный файл для GLu32 библиотеки
#include <gl\glaux.h>		// Заголовочный файл для GLaux библиотеки
#include <gl\glext.h>

#include "GameMenu.h"

const float WindowDepth=10000;
const float WindowFogDensity=0.003;
const float AngleDepth=10240;
//global pointers to ProjectGL class
LRESULT CALLBACK NWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
//delete

class ProjectGL
{
private:
    GameMenu *pGM;
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
    int WinFlag;
    bool fullscreen;
    void (*FOnKeyDown)(char);
    void (*FOnKeyUp)(char);
//
private:
    void InitGL();
    void ReSizeGLScene();
public:
    ProjectGL();
    ~ProjectGL();
    bool CreateGLWindow(HINSTANCE);
    bool DeleteGLWindow();
    LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
//set window params
    void SetScreenSize(int ScreenX,int ScreenY,bool FullScreen=false);
    void DrawGLScene();
    void SetGameMenu(GameMenu*);
    void SetOnKeyDown(void(*OnKeyPress)(char key));
    void SetOnKeyUp(void(*OnKeyPress)(char key));
    void SetOnKeyFree(void(*OnKeyUp)(char key));
//
    bool GetKeys(unsigned char key);
    int LoadGLTextures(char* file);
};

#endif // PROJECTGL_H
