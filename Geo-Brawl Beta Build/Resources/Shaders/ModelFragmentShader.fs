#version 450 core

in vec2 fragTexCoords;
out vec4 color;

uniform vec4 fragcolor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

uniform sampler2D texture_diffuse1;

void main()
{
	color = texture(texture_diffuse1, fragTexCoords) * fragcolor;
}
