#version 450 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;

uniform mat4 MVP;

out vec4 fragcolor;

void main(void)
{	
	gl_Position = MVP * vec4(in_position, 1.0);
	fragcolor = in_color;
} 
