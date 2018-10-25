#version 450 core

out vec4 color;

in vec4 fragcolor;
in vec4 mWorldPos;
in vec2 fragTexCoord;

uniform vec3 cameraPos;
uniform sampler2D tex;
uniform vec4 vFogColor;

void main()
{	
	float d = distance(mWorldPos.xyz, cameraPos);
	float lerp = (d - 5.0f)/10.f;
	lerp = clamp(lerp, 0.0, 1.0);
	color = texture(tex, fragTexCoord) * fragcolor;
	color = mix(color, vFogColor, lerp);
} 

