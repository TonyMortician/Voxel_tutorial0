// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;

#pragma comment (lib,"Gdiplus.lib")
#include <glew.h>
#include <wglew.h>
#include <gl\gl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>
#include <filesystem>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <functional>
#include <stb_image.h>
#include <map>
