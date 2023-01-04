#include "EDITOR.h"

void EDITOR::init(HWND win, HINSTANCE hInstance)
{
	using namespace std::placeholders;	
	resManager.init(win, hInstance);
	renderer.init(&resManager);
	sModel.init(&resManager);

	pallete.init(&resManager);
	pallete.loadPalleteText();	
}
