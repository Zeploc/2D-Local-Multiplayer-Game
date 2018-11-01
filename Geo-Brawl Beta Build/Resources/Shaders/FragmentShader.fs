#version 450 core

out vec4 color;

in vec4 fragcolor;


void main(void)
{	
	color = fragcolor;
} 

