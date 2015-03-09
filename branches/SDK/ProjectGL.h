#ifndef PROJECTGL_H
#define PROJECTGL_H

#include "gl.h"			// Заголовочный файл для OpenGL32 библиотеки
#include "glaux.h"

LRESULT CALLBACK NWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

class ProjectGL
{
private:
    bool created;
    GLuint DisplayList;
    GLuint Texture[1024][1];
    GLuint Texturei;
    GLuint TextureActive;
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
    float WindowFogDensity;
    float WindowDepth;
    float WindowAngle;
    float WindowNear;
    void (*FOnKeyDown)(char);
    void (*FOnKeyUp)(char);
    void (*FOnMouseMove)(int,int);
    //on click
    //on idle
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
    void SetOnKeyDown(void(*OnKeyPress)(char key));
    void SetOnKeyUp(void(*OnKeyPress)(char key));
    void SetOnMouseMove(void(*OnMouseMove)(int x,int y));
    void SetScreenSize(int x,int y,bool fullscreen);
//Drawing
    void MatrixSave();
    void MatrixLoad();
    void ListCompile(int number);
    void ListExecute(int number);
    void ListFinish();
    void EnableMode(char TranslateKey);
    void ClearGLScene();
    void CameraMove(float x,float y,float z);
    void CameraRotate(float angle,float x,float y,float z);
    void DrawGLScene(float *vertex,float *text, float *normal,int *face,int facei);/* comment */
    void DrawGLScene(float *vertex,int *face,int facei);/* comment */
    void TextureActivate(int);
    void ShowGLScene();
//
    int LoadGLTextures(char* file);
    bool GetKeys(unsigned char key);
};

/*
EnableMode
1 - Scale to window coordinates are -1 to 1 , -1 to 1 , -1
DrawGLScene: translatekey to:
*/
#endif // PROJECTGL_H

