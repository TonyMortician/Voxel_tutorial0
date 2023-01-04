#include "RENDERER.h"


void RENDERER::init(RES_MANAGER* res)
{
	resManager = res;
	rModel.init(res);	
}

void RENDERER::render()
{
	if (resManager->isSet)
	{
		rModel.renderModel();
	}
}