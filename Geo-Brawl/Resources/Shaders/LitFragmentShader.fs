#version 450 core

out vec4 color;

in vec4 fragcolor;
in vec2 fragTexCoord;
in vec3 fragPos;
in vec3 fragNormal;

uniform int bIsTex = 1;
uniform sampler2D tex;
uniform float ambientStr = 0.1f;
uniform vec3 ambientColor = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightPos;// = vec3(-5.0f, 5.0f, 0.5f);

// Specular
uniform float lightSpecStr = 1.0f;
uniform vec3 camPos = vec3(1.0f, 1.0f, 3.0f);
uniform float shininess = 32.0f;


void main(void)
{	
	// Light Direction
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(fragPos - lightPos);
	
	// Specular Highlight
	vec3 negViewDir = normalize(camPos - fragPos);
	vec3 reflectDir = reflect(lightDir, norm);
	float spec = pow(max(dot(negViewDir , reflectDir), 0.0f), shininess);
	vec3 specular = lightSpecStr * spec * lightColor;


	vec3 ambient = ambientStr * ambientColor;
	
	
	// Diffuse Coloring
	float diffuseStr = max(dot(norm, -lightDir), 0.0f);
	vec3 diffuse = diffuseStr * lightColor;
	
	if (bIsTex == 1) color = vec4(ambient + diffuse + specular, 1.0f) * texture(tex, fragTexCoord) * fragcolor;
	else color = vec4(ambient + diffuse + specular, 1.0f) * fragcolor;
} 

