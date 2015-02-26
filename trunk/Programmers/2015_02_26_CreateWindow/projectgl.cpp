#include <iostream>
#include <fstream>
#include "utime.h"
#include "projectgl.h"

ProjectGL *lGL;//this

ProjectGL::ProjectGL()
{
    created=false;
    for(int i=0;i<256;i++)
        keys[i]=false;
    TexturaWoLoadedc=0;
    lGL=this;
// default window;
    WinY=800;WinX=600;fullscreen=false;
    FOnKeyDown=NULL;
    FOnKeyUp=NULL;
    pfd={
        sizeof(PIXELFORMATDESCRIPTOR),	// ������ ���� ���������
        1,				// ����� ������ (?)
        PFD_DRAW_TO_WINDOW |// ������ ��� ����
        PFD_SUPPORT_OPENGL |// ������ ��� OpenGL
        PFD_DOUBLEBUFFER,// ������ ��� �������� ������
        PFD_TYPE_RGBA,	// ��������� RGBA ������
        16,				// ����� 16 ��� ������� �����
        0, 0, 0, 0, 0, 0,// ������������� �������� ����� (?)
        0,				// ��� ������ ������������
        0,				// ��������� ��� ������������ (?)
        0,				// ��� ������ �����������
        0, 0, 0, 0,		// ���� ����������� ������������ (?)
        16,				// 16 ������ Z-����� (����� �������)
        0,				// ��� ������ ����������
        0,				// ��� ��������������� ������� (?)
        PFD_MAIN_PLANE,	// ������� ���� ���������
        0,				// ������ (?)
        0, 0, 0			// ����� ���� ������������ (?)
    };
}

ProjectGL::~ProjectGL()
{
    if(created)
        DeleteGLWindow();
}

bool ProjectGL::CreateGLWindow(HINSTANCE hI)
{
    WNDCLASS wc; // ��������� ������ Windows ��� ��������� ���� ����
    int xx=(fullscreen)?0:256;
//
    wc.style=CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
    wc.lpfnWndProc=(WNDPROC)NWndProc;
    wc.cbClsExtra=0;
    wc.cbWndExtra=0;
    wc.hInstance=hI;
    wc.hIcon=NULL;
    wc.hCursor=LoadCursor(NULL,IDC_ARROW);
    wc.hbrBackground=NULL;
    wc.lpszMenuName=NULL;
    wc.lpszClassName="OpenGL WinClass";
//
    if(!RegisterClass(&wc)){
        MessageBox(NULL,"can't register class","Error",MB_OK|MB_ICONERROR);
        return false;}
    if(!(hWnd = CreateWindow(
                "OpenGL WinClass",
                "TEST",	// ��������� ������ ����
                WinFlag,
                xx,0,WinX,WinY,		// ������ � ������ ����
                NULL,
                NULL,
                hI,
                NULL))){
        MessageBox(NULL,"Can't create window","Error",MB_OK|MB_ICONERROR);
        return false;}
    DEVMODE dmScreenSettings;			// ����� ������
    memset(&dmScreenSettings,0,sizeof(DEVMODE));	// ������� ��� �������� ���������
    dmScreenSettings.dmSize=sizeof(DEVMODE);		// ������ ��������� Devmode
    dmScreenSettings.dmPelsWidth=WinX;			// ������ ������
    dmScreenSettings.dmPelsHeight=WinY;			// ������ ������
    dmScreenSettings.dmFields=DM_PELSWIDTH|DM_PELSHEIGHT;	// ����� �������
    if (fullscreen)
        ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN);
    ShowWindow(hWnd,SW_SHOW);
    UpdateWindow(hWnd);
    SetFocus(hWnd);
    created=true;//*/
    return true;
}

bool ProjectGL::DeleteGLWindow()
{
    created=false;
    SendMessage(hWnd,WM_CLOSE,0,0);
    return true;
}

//
void ProjectGL::SetScreenSize(int a,int b,bool c)
{
    WinX=a;
    WinY=b;
    fullscreen=c;
    WinFlag=(c)?(WS_POPUP|WS_CLIPCHILDREN|WS_CLIPSIBLINGS):(WS_EX_APPWINDOW);
    if(created)
        ReSizeGLScene();
}

void ProjectGL::SetOnKeyDown(void(*OnKeyPress)(char key))
{
    FOnKeyDown=OnKeyPress;
}

void ProjectGL::SetOnKeyUp(void(*OnKeyPress)(char key))
{
    FOnKeyUp=OnKeyPress;
}

void ProjectGL::SetGameMenu(GameMenu *arg)
{
    pGM=arg;
}

//
void ProjectGL::DrawGLScene()
{
    //pTM->TestUtoki();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ������� ������ � ������ �������
    glLoadIdentity();				// ����� ���������'
//

//
    glLoadIdentity();				// ����� ���������
    SwapBuffers(hDC);

}

int ProjectGL::LoadGLTextures(char *file)
{
    glGenTextures(1,TexturaWoLoaded[TexturaWoLoadedc]);
    glBindTexture(GL_TEXTURE_2D,TexturaWoLoaded[TexturaWoLoadedc][0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    AUX_RGBImageRec *texture;
    texture=auxDIBImageLoad(file);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture->sizeX,texture->sizeY,0,GL_RGB,GL_UNSIGNED_BYTE,texture->data);
    return TexturaWoLoadedc++;
}

void ProjectGL::InitGL()	// ������� ����� �������� ���� GL
{
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);		// ��������� ������� ������ �������
    glDepthFunc(GL_LESS);	// ��� ����� �������
    glEnable(GL_DEPTH_TEST);// ��������� ���� �������
    glShadeModel(GL_SMOOTH);// ��������� ������� �������� �����������
    glMatrixMode(GL_PROJECTION);// ����� ������� ��������
//
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//Anti Aliasing
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
//
    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_FILL/*LINE*/);
}

void ProjectGL::ReSizeGLScene()
{
    glViewport(0,0,WinX, WinY);
    glMatrixMode(GL_PROJECTION);// ����� ������� ��������
    glLoadIdentity();			// ����� ������� ��������
    glFrustum(-float(WinX)/AngleDepth,float(WinX)/AngleDepth,-float(WinY)/AngleDepth,float(WinY)/AngleDepth,0.1,WindowDepth);
    //gluPerspective(45,(GLfloat)x/(GLfloat)y,0.1f,WindowDepth);
    glMatrixMode(GL_MODELVIEW);	// ����� ������� ��������� ������
}

LRESULT NWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    return lGL->WndProc(hWnd,message,wParam,lParam);
}

LRESULT ProjectGL::WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    RECT Screen;		// ������������ ������� ��� �������� ����
    GLuint PixelFormat;
//    logfile<<pTM->GetUtime()<<"\t"<<message<<std::endl;
    switch (message){
    case WM_CREATE:
        hDC=GetDC(hWnd);	// �������� �������� ���������� ��� ����
        PixelFormat=ChoosePixelFormat(hDC,&(pfd));
        if(!PixelFormat){
            MessageBox(0,"PixelFormat ha arimasen","Error",MB_OK|MB_ICONERROR);
            PostQuitMessage(0);// ��� ��������� �������, ��� ��������� ������ ����������
            break;}
        if(!SetPixelFormat(hDC,PixelFormat,&pfd)){
            MessageBox(0,"PixelFormat wo oku dekimasen","Error",MB_OK|MB_ICONERROR);
            PostQuitMessage(0);
            break;}
        hRC=wglCreateContext(hDC);
        if(!hRC){
            MessageBox(0,"Rendering Contekusuto wo tsukuru dekimasen.","Error",MB_OK|MB_ICONERROR);
            PostQuitMessage(0);
            break;}
        if(!wglMakeCurrent(hDC,hRC)){
            MessageBox(0,"DC wo oku dekimasen","Error",MB_OK|MB_ICONERROR);
            PostQuitMessage(0);
            break;}
        GetClientRect(hWnd,&Screen);
        InitGL();
        break;
    case WM_DESTROY:
    case WM_CLOSE:
        if(fullscreen)
            ChangeDisplaySettings(NULL,0);
        wglMakeCurrent(hDC,NULL);
        wglDeleteContext(hRC);
        ReleaseDC(hWnd,hDC);
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
        if(created){
            keys[wParam]=true;
            if(FOnKeyDown)
                (*FOnKeyDown)(wParam);}
        break;
    case WM_KEYUP:
        if(created){
            keys[wParam]=false;
            if(FOnKeyDown)
                (*FOnKeyUp)(wParam);}
        break;
    case WM_SIZE:
        SetScreenSize(LOWORD(lParam),HIWORD(lParam),fullscreen);
        break;
//    case WM_MOUSEMOVE:
// WHY CAN NOT I USE GET_X_LPARAM()
//        OnMouseMove(LOWORD(lParam),HIWORD(lParam));
//        break;
    default:
        return(DefWindowProc(hWnd,message,wParam,lParam));
    }
    return(0);
}

bool ProjectGL::GetKeys(unsigned char key)
{
    return keys[key];
}

