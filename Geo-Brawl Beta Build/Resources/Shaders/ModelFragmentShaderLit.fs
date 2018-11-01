#version 450 core

in vec2 fragTexCoords;
in vec3 fragPos;
in vec3 fragNormal;
out vec4 color;

uniform vec4 fragcolor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

uniform sampler2D texture_diffuse1;

uniform float ambientStr = 0.1f;
uniform vec3 ambientColor = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightPos = vec3(30, 2, 30);// = vec3(-5.0f, 5.0f, 0.5f);

// Specular
uniform float lightSpecStr = 1.0f; // = 1.0f;
uniform vec3 camPos = vec3(1.0f, 1.0f, 3.0f); // = glm::vec3(1.0f, 1.0f, 3.0f);
uniform float shininess = 32.0f; // = 32.0f;

void main()
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
	
	color = vec4(ambient + diffuse + specular, 1.0f) * texture(texture_diffuse1, fragTexCoords) * fragcolor;
}
