#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colorVal;
layout (location = 2) in mat4 transfMatrix;
out vec3 vcolor;
void main()
{
	gl_Position = transfMatrix*vec4(position,1);
	vcolor = colorVal;
}