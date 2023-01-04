#pragma once

#include "framework.h"
#include "Shader.h"
#include "camera.h"
#include "camera01.h"
#include "EDITOR.h"

enum BUFFERS{POINT_BUFFER, COLOR_BUFFER, ATOMIC_BUFFER};

struct plane
{
    GLuint vao;
    GLuint buffers[2];  
};

struct land
{
    GLuint textures[4];
    GLuint h_textures[4];  
};

LRESULT CALLBACK GLWindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

class Core
{
public:
    Core(HINSTANCE hInstance);
    HDC DC;
    HWND WND;
  
    HGLRC RC;
    std::ofstream  log;
    HINSTANCE hInst;
    MSG Msg;
    static Core* pointer;      
    WNDCLASSEX           wndTemplate;   
    DWORD Main_loop();
    void Finish();
    //------------------------
    void Render();
   
    //------------------------
       
    //-------------------------
 

    //-------------------------
    // DATA BLOCK I
    //-------------------------
   
    GLuint p_num;
   
    glm::mat4 mod_dimensions;
    int points_to_draw;   
    HWND hwnds[5];
    void init_data();   
    void math();
    bool is_set{ 0 };
    glm::vec3 view_dir;
    glm::mat4 view_mat;
    GLuint vao_m;
    GLuint vbo_m;
    GLuint vao_m2;       

    plane main_plane;

   
    glm::vec3 view_pos;

    camera cam_0;
    land sector_0;   
    Shader land_shader;
    Shader renderer;
    Shader loader;


   
    void move_camera(unsigned int dir);
   
    glm::vec4 pos;  
  
      

   
    GLuint subsector;
    

    EDITOR editor;
    GLuint renderMode{ 0 };

    camera01 cam2;


    glm::ivec2 resolution{ 1440, 900 };

    void initContextWindow();
    void initGLWindow();
};

