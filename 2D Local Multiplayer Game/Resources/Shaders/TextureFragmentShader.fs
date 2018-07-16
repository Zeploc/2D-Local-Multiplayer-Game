#version 450 core

out vec4 color;

in vec4 fragcolor;
in vec2 fragTexCoord;

uniform sampler2D tex;

void main(void)
{	
	color = texture(tex, fragTexCoord) * fragcolor;
} 

