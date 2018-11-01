#version 450 core

layout(location = 0) in vec3 in_position;
layout(location = 1) uniform vec4 in_color;
layout(location = 2) in vec2 texCoord;


uniform mat4 MVP;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;


out vec4 fragcolor;
out vec2 fragTexCoord;
out vec4 mWorldPos;

void main(void)
{	
	mWorldPos = model *vec4(in_position, 1.0);
	gl_Position = proj * view * mWorldPos;
	fragcolor = in_color;
	fragTexCoord = texCoord;
	
} 
