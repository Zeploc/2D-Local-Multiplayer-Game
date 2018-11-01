#version 450 core

// ## TEXTURE ###
out vec4 color;

in vec4 fragcolor;
in vec2 fragTexCoord;

uniform sampler2D tex;
uniform int bIsTex = 1;

// ### FOG ###
in vec4 mWorldPos;

uniform int bFog = 0;
uniform vec4 vFogColor;
uniform vec3 cameraPos;

uniform float StartFog = 5.0f;
uniform float EndFog = 10.0f;

void SetFogColour();

void main(void)
{	
	if (bIsTex == 1) color = texture(tex, fragTexCoord) * fragcolor;
	else color = fragcolor;
	
	if (bFog == 1)
	{
		SetFogColour();
	}
	if (color.a < 0.3)
	{
		discard;
	}
} 

void SetFogColour()
{
	float d = distance(mWorldPos.xyz, cameraPos);
	float lerp = (d - StartFog)/EndFog;
	lerp = clamp(lerp, 0.0, 1.0);
	color = mix(color, vFogColor, lerp);
}

