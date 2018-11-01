#version 450 core

in vec2 fragTexCoord;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, fragTexCoord).a);
	color = vec4(textColor, 1.0) * sampled;
}