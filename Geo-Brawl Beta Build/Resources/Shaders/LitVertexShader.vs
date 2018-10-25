#version 450 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;

uniform mat4 MVP; 

out vec4 fragcolor;
out vec2 fragTexCoord;
out vec3 fragPos;
out vec3 fragNormal;

uniform mat4 model;

void main(void)
{	

	gl_Position = MVP * vec4(in_position, 1.0);
	fragPos = vec3(model * vec4(in_position, 1.0f));
	fragNormal = mat3(transpose(inverse(model))) * normal;
	fragcolor = in_color;
	fragTexCoord = texCoord;
} 
