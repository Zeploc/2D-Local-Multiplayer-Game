#version 450 core

in vec2 fragTexCoord;
out vec4 color;

uniform int bIsTex;
uniform sampler2D tex;
uniform vec4 Color;

void main()
{
	if (bIsTex == 1)
	{
		color = texture(tex, fragTexCoord) * Color;
	}
	else if (bIsTex == 0)
	{
		color = Color;
	}
}