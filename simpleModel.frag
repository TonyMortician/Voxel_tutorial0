#version 460 core

out vec4 color;


in vec4 col;
in flat uint exist;

void main()
{		

	if(exist==0) discard;
	else color = col;
	
}
