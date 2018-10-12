#version 450 core

// ## TEXTURE ###
out vec4 color;

in vec4 fragcolor;
in vec2 fragTexCoord;

uniform sampler2D tex;
uniform float dTime;


void main(void)
{	
	
	// distance from center of image, used to adjust blur
	float d = length(fragTexCoord - vec2(0.5,0.5));
	
	// blur amount
	float blur = 0.0;	
	blur = (1.0 + sin(dTime*6.0)) * 0.5;
	blur *= 1.0 + sin(dTime*16.0) * 0.5;
	blur = pow(blur, 3.0);
	blur *= 0.05;
	// reduce blur towards center
	blur *= d;
	
	// final color
    vec3 col;
    col.r = texture( tex, vec2(fragTexCoord.x+blur,fragTexCoord.y) ).r;
    col.g = texture( tex, fragTexCoord ).g;
    col.b = texture( tex, vec2(fragTexCoord.x-blur,fragTexCoord.y) ).b;
	
	// scanline
	float scanline = sin(fragTexCoord.y*800.0)*0.04;
	col -= scanline;
	
	// vignette
	col *= 1.0 - d * 0.5;
	
    color = vec4(col,1.0);
	//color = texture(tex, fragTexCoord);
} 


