

// REVISION: 20/11/22



#version 460 core
layout (binding = 0, r32ui) uniform readonly uimage3D object;
layout (binding = 1, rgba8) uniform image2D pallete;



uniform mat4 mvm;
uniform float pSize;

uniform vec3 tSize;
uniform vec3 mSize;

out flat uint exist;
out vec4 col;

const uint isSet = 268435456; 

void main()
{  
	
	uint vertexN = gl_VertexID;
	
	
	uint x = gl_VertexID % uint(tSize.x);
	uint z = gl_VertexID / uint(tSize.x * tSize.y);
	uint y = (gl_VertexID % uint(tSize.x * tSize.y)) / uint(tSize.x);
	
	/*
	uint x = gl_VertexID % 16;
	uint z = gl_VertexID / uint(16 * 16);
	uint y = gl_VertexID / 16;
	*/
	
	vec3 steps;
	steps.x = 0.02f;
	steps.y = 0.02f;
	steps.z = 0.02f;
	vec4 tPos;
	tPos.x = float(x)*steps.x;
	tPos.y = float(y)*steps.y;
	tPos.z = float(z)*steps.z;		
	tPos.w = 1.0f;
	
	gl_Position =  mvm * tPos;		
	gl_PointSize = pSize;
	
	
	
					  
    
	
	ivec2 textPos;
	uint material;
	uint color;
	uint val;
	val = imageLoad(object, ivec3(x, y, z)).x;
	exist = ((val & isSet) >> 28);
	if(exist==1)
	{
	color = (val&255);
	material = ((val&3840)>>8);	
	col = imageLoad(pallete, ivec2(material, color));	
	}
}



