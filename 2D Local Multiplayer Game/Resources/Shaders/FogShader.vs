#version 450 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;


uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec4 fragcolor;
out vec4 mWorldPos;

void main()
{	
	mWorldPos = model *vec4(in_position, 1.0);
	gl_Position = proj * view * mWorldPos;
	fragcolor = in_color;
} 
