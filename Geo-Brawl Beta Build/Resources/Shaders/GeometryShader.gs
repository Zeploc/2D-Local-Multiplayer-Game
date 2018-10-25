#version 430 core

layout (points) in;
layout (triangle_strip, max_vertices = 10) out;

out vec4 outColor;

in VS_GS_VERTEX{
	in vec4 position;
	in vec4 color;
	in mat4 mvp;
}gs_in[];

void main()
{
	outColor = gs_in[0].color;
	
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(0.0f, -0.5f, 0.0f, 0.0f);
    EmitVertex();
    gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(1.0f, 0.24f, 0.0f, 0.0f);
    EmitVertex();
    gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(-1.0f, 0.24f, 0.0f, 0.0f);
    EmitVertex();

    EndPrimitive();

    gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(-0.62f, -1.0f, 0.0f, 0.0f);
    EmitVertex();
    gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(0.0f, 1.0f, 0.0f, 0.0f);
    EmitVertex();
    gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(0.38f, -0.24f, 0.0f, 0.0f);
    EmitVertex();

    EndPrimitive();

    gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(0.62f, -1.0f, 0.0f, 0.0f);
    EmitVertex();
    gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(-1.0f, 0.24f, 0.0f, 0.0f);
    EmitVertex();
    gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(0.38f, -0.24f, 0.0f, 0.0f);
    EmitVertex();

}