#version 450 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec2 texCoord;


out vec4 fragcolor;
out vec2 fragTexCoord;

void main(void)
{	
	gl_Position = vec4(in_position, 1.0);
	fragcolor = in_color;
	fragTexCoord = texCoord;
	
} 
