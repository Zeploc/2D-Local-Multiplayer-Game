#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec3 fragNormal;
out vec3 fragPos;
out vec2 fragTexCoord;

uniform mat4 MVP;
uniform mat4 model;

void main()
{
	gl_Position = MVP * vec4(position, 1.0f);
	fragNormal = mat3(transpose(inverse(model))) * normal;
	fragPos = vec3(model * vec4(position, 1.0f));
	fragTexCoord = texCoord;
}