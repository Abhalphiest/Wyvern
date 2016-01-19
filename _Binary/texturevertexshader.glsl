#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvCoord;
layout (location = 2) in mat4 transfMatrix;
out vec2 uv;
uniform mat4 projection;
uniform mat4 view;
void main()
{
	gl_Position = projection*view*transfMatrix*vec4(position,1);
	uv = uvCoord;
}