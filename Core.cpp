#include "Core.h"
//#define STB_IMAGE_IMPLEMENTATION   
Core* Core::pointer = nullptr;
//#include <stb_image.h>
GLuint id;

Core::Core(HINSTANCE HINST)
{
    hInst = HINST;
    DC = 0;
    WND = 0;
    RC = 0;
    log.open("log", std::ios::out | std::ios::trunc);
    pointer = this;
}



DWORD Core::Main_loop()
{    
    int prev_time = GetTickCount();
    pointer = this;
    while (1)
    {          
    
            if (GetTickCount() > prev_time + 1)
            {
                pointer->Render();
                SwapBuffers(DC);
                prev_time = GetTickCount();
            }
            if (GetMessage(&Msg, NULL, 0, 0))
            {
                TranslateMessage(&Msg);
                DispatchMessage(&Msg);
            }
            else
            {
                return Msg.wParam;
            }       
      
    }
    
}

void Core::Finish()
{
    log.close();
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(RC);
    ReleaseDC(WND, DC);
    DestroyWindow(WND);
}

void Core::Render()
{
  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    if (is_set)
    {
       pointer->editor.renderer.render();        
    }
 
}

void Core::init_data()
{  
    //editor.log = &log;
 
  
}

void Core::move_camera(unsigned int dir)
{
    switch (dir)
    {
    case FORWARD:
        if (pos.x < 3750.0f) pos.x += 50;
        break;
    case BACKWARD:
        if (pos.x > 1250.0f) pos.x -= 50;
        break;
    case LEFT:
        if (pos.y < 3750.0f) pos.y += 50;
        break;
    case RIGHT:
        if (pos.y > 1250.0f) pos.y -= 50;
        break;
  
    default:
        break;
    }   
}

void Core::math()
{
    using namespace glm;
/*    vec3 lDir = vec3(-0.0f, -0.5f, -0.8f);
    vec3 camPos = vec3(0.0f, -0.0f, -5.0f);
    vec lpos = vec3(5.0f, 5.0f, 2.0f);
    vec3 tPos = vec3(15, 15, 5);
    vec3 wPos = vec3((15 - 16 / 2) * 0.0625, (15 - 16 / 2) * 0.0625, 5 * 0.0625 - 10.0f);
    vec3 dir0 = camPos - wPos;
    vec3 dir1 = lpos - wPos;

    log << "d0: " << dir0.x << " " << dir0.y << " " << dir0.z << std::endl;
    log << "d1: " << dir1.x << " " << dir1.y << " " << dir1.z << std::endl;
    log << "DOT: " << dot(normalize(dir0), normalize(dir1)) << std::endl;
    /* ivec3 finalPos = ivec3(tPos + lDir * float( (k + 2)));
    for (int i = 0; i < 16; i++)
    {
        finalPos = ivec3(tPos + lDir * float((i + 2)));
        log << "I: " << i << " " << finalPos.x << " " << finalPos.y << " " << finalPos.z << std::endl;
    } */

    vec3 dir0 = vec3(0.0f, 1.0f, 0.0f);
    vec3 dir1 = vec3(0.5f, -0.5f, 0.0f);
    //float d = dot(normalize(dir0), normalize(dir1));
    //log << "DOT: " << d << std::endl;

    vec3 pointPos(15.8f, 0.1f, 0.6f);
    float xp, yp, zp;
    xp = fract(pointPos.x) - 0.5f;
    yp = fract(pointPos.y) - 0.5f;
    zp = fract(pointPos.z) - 0.5f;

    float d[6];
    float dr;

    d[0] = distance(vec3(xp, yp, zp), vec3(-1.0f, yp, zp));
    d[1] = distance(vec3(xp, yp, zp), vec3(1.0f, yp, zp));
    d[2] = distance(vec3(xp, yp, zp), vec3(xp, -1.0f, zp));
    d[3] = distance(vec3(xp, yp, zp), vec3(xp, 1.0f, zp));
    d[4] = distance(vec3(xp, yp, zp), vec3(xp, yp, 1.0f));
    d[5] = distance(vec3(xp, yp, zp), vec3(xp, yp, -1.0f));

    dr = min(d[0], d[1]);
    dr = min(dr, d[2]);
    dr = min(dr, d[3]);
    dr = min(dr, d[4]);
    dr = min(dr, d[5]);

    int i;
    if (dr == d[0]) i=0;
    if (dr == d[1]) i = 1;
    if (dr == d[2]) i = 2;
    if (dr == d[3]) i = 3;
    if (dr == d[4]) i = 4;
    if (dr == d[5]) i = 5;

    log << "RES: " << i << std::endl;

    vec3 lPos = vec3(5.0f, 5.0f, -2.0f);
    //pointPos.z -= 10.0f;
    vec3 normals[6] = { vec3(-1.0f, 0.0f, 0.0f), vec3(+1.0f, 0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f) };
    vec3 wPointPos = vec3((pointPos.x - 15 / 2 )* 0.0625 , (pointPos.y - 15 / 2) * 0.0625 , pointPos.z * 0.0625 - 10.0f);
    vec3 lDir = lPos - wPointPos;
    float d2 = dot(normalize(lDir), normals[i]);
    log << "D: " << d2 << std::endl;
}


void Core::initContextWindow()
{
    WNDCLASSEX    wc2;
    wc2.cbSize = sizeof(WNDCLASSEX);
    // wc2.style = CS_HREDRAW | CS_VREDRAW ;
    wc2.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc2.lpfnWndProc = (WNDPROC)GLWindowProcedure;
    wc2.cbClsExtra = 0;
    wc2.cbWndExtra = 0;
    wc2.hInstance = hInst;
    wc2.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(101));
    wc2.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(101));
    wc2.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc2.lpszMenuName = NULL;
    wc2.lpszClassName = L"Window";


    if (!RegisterClassEx(&wc2))
    {
        MessageBox(NULL, L"Failed To Register The Window Class.", L"Error", MB_OK | MB_ICONERROR);
    }

    HWND fakeWND = 0;

    fakeWND = CreateWindow(L"Window", L"window",
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        0, 0, 1, 1, NULL, NULL, hInst, NULL);

    HDC fakeDC = GetDC(fakeWND);

    PIXELFORMATDESCRIPTOR fakePFD;
    ZeroMemory(&fakePFD, sizeof(fakePFD));
    fakePFD.nSize = sizeof(fakePFD);
    fakePFD.nVersion = 1;
    fakePFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    fakePFD.iPixelType = PFD_TYPE_RGBA;
    fakePFD.cColorBits = 32;
    fakePFD.cAlphaBits = 8;
    fakePFD.cDepthBits = 24;

    int fakePFDID = ChoosePixelFormat(fakeDC, &fakePFD);
    if (fakePFDID == 0) {
        MessageBox(NULL, L"Could not choose pixel format.",
            L"Error", MB_OK);
    }

    if (SetPixelFormat(fakeDC, fakePFDID, &fakePFD) == false) {
        MessageBox(NULL, L"Could not set pixel format.",
            L"Error", MB_OK);
    }

    HGLRC fakeRC = wglCreateContext(fakeDC);    // Rendering Contex
    if (fakeRC == 0) {
        MessageBox(NULL, L"Could not create fake context.",
            L"Error", MB_OK);
    }

    if (wglMakeCurrent(fakeDC, fakeRC) == false) {
        MessageBox(NULL, L"Could not make fake context current.",
            L"Error", MB_OK);
    }

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err == GLEW_OK)
    {

    }
    else
    {
        MessageBox(NULL, L"Could not init GLEW.",
            L"Error", MB_OK);
    }
    
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(fakeRC);
    ReleaseDC(fakeWND, fakeDC);
    DestroyWindow(fakeWND);

    pointer = this;

}

void Core::initGLWindow()
{
    WNDCLASSEX    wc2;
    wc2.cbSize = sizeof(WNDCLASSEX);
    // wc2.style = CS_HREDRAW | CS_VREDRAW ;
    wc2.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc2.lpfnWndProc = (WNDPROC)GLWindowProcedure;
    wc2.cbClsExtra = 0;
    wc2.cbWndExtra = 0;
    wc2.hInstance = hInst;
    wc2.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(101));
    wc2.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(101));
    wc2.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc2.lpszMenuName = NULL;
    wc2.lpszClassName = L"GLWindow";


    if (!RegisterClassEx(&wc2))
    {
        MessageBox(NULL, L"Failed To Register The GLWindow Class.", L"Error", MB_OK | MB_ICONERROR);
    }

  
    WND = 0;
    WND = CreateWindow(
        L"GLWindow", L"OpenGL Window",
        WS_CAPTION | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        100, 100,
        resolution.x, resolution.y, // Win Creation
        NULL, NULL,
        hInst, NULL);

    DC = GetDC(WND);
    const int pixelAttribs[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_ALPHA_BITS_ARB, 8,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
        WGL_SAMPLES_ARB, 4,
        0
    };

    int pixelFormatID; UINT numFormats;
    bool status = wglChoosePixelFormatARB(DC, pixelAttribs, NULL, 1, &pixelFormatID, &numFormats);

    if (status == false || numFormats == 0) {
        MessageBox(NULL, L"Could not choose pixel format.",
            L"Error", MB_OK);
    }

    PIXELFORMATDESCRIPTOR PFD;
    DescribePixelFormat(DC, pixelFormatID, sizeof(PFD), &PFD);
    SetPixelFormat(DC, pixelFormatID, &PFD);


    int  contextAttribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    RC = wglCreateContextAttribsARB(DC, 0, contextAttribs);
    if (RC == NULL) {
        MessageBox(NULL, L"Could not create opengl context.",
            L"Error", MB_OK); ;
    }

 
    if (!wglMakeCurrent(DC, RC)) {
        MessageBox(NULL, L"Could not make opengl context current.",
            L"Error", MB_OK);
    }

    ShowWindow(WND, 1);
    UpdateWindow(WND);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, resolution.x, resolution.y); // Viewport set
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
     


    glEnable(GL_PROGRAM_POINT_SIZE); 
    glEnable(GL_MULTISAMPLE);  
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_NICEST);
    editor.init(WND, hInst);
    is_set = true;
}


LRESULT CALLBACK GLWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    POINT pt;
    GLuint localMode;
    static HWND buttons[10];
    static HWND track;
    static HWND brushMenu;
    static float wheel_delta{ 0.0f };
    static POINT prevPos;
    static POINT actPos;
    static int pitchDelta;
    static int yawDelta;
    PAINTSTRUCT ps;
    HDC hdc;
    Core* pointer = Core::pointer;
    switch (message)
    {
    case WM_PAINT:


        break;
    case WM_MOUSEWHEEL:

        break;
    case WM_MOUSEMOVE:


        break;
    case WM_RBUTTONDOWN:
     
        break;
    case WM_LBUTTONDOWN:
      
        break;
    case WM_CREATE:



        break;
    case WM_HSCROLL:

        break;
    case WM_KEYDOWN:
        if (wParam == 'R')
        {
       
        }
        if (wParam == 'M')
        {
       

        }
        if (wParam == 'C')
        {
         
        }
        if (wParam == 'X')
        {
     
        }
        if (wParam == 'I')
        {
      

        }
        if (wParam == 'O')
        {
  
        }
        if (wParam == 'V')
        {
            pointer->editor.sModel.createModel();
            pointer->editor.resManager.modelTexture = pointer->editor.sModel.texture;
            pointer->editor.resManager.pNum = pointer->editor.sModel.tSize.x * pointer->editor.sModel.tSize.y * pointer->editor.sModel.tSize.z;
            pointer->editor.resManager.modelTSize = pointer->editor.sModel.tSize;
            pointer->editor.resManager.modelMSize = pointer->editor.sModel.mSize;
            pointer->editor.resManager.palleteTexture = pointer->editor.pallete.palleteText;
            pointer->editor.resManager.isSet = true;
        }
        if (wParam == 'J')
        {
            pointer->editor.renderer.rModel.cam2.setView(2);
        }
        if (wParam == 'U')
        {
            pointer->editor.renderer.rModel.cam2.setView(5);
        }
        if (wParam == 'M')
        {
            pointer->editor.renderer.rModel.cam2.setView(4);
        }
        if (wParam == 'D')
        {
   
        }
        if (wParam == 'L')
        {
   
        }
        if (wParam == 'H')
        {
   
        }
        if (wParam == 'J')
        {
        
        }
        if (wParam == 'K')
        {
     
        }
        if (wParam == VK_UP)
        {
          
        }
        if (wParam == VK_DOWN)
        {
          
        }
        if (wParam == VK_LEFT)
        {
         
        }
        if (wParam == VK_RIGHT)
        {
        
        }
        if (wParam == VK_SPACE)
        {
           

        }
        if (wParam == VK_CONTROL)
        {
         

        }
        if (wParam == VK_ADD)
        {
            pointer->editor.resManager.pSize += 1.0f;

        }
        if (wParam == VK_SUBTRACT)
        {
            pointer->editor.resManager.pSize -= 1.0f;
        }
        if (wParam == 'Q')
        {
         
        }
        if (wParam == 'E')
        {
    
        }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 0:
       
            break;
        case 1:
         
          
            break;
        case 2:
          
         
            break;
        case 3:
    
         
            break;
        case 4:
        
            break;
        case 5:
       
            break;
        case 6:
      
            break;
        case 7:
    
            break;
        case 8:

     
            break;
        }
        break;
    case WM_TIMER:
        if (wParam == 9999)
        {
            pointer->Render();
            SwapBuffers(pointer->DC);
        }
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}