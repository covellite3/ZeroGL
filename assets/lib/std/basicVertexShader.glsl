#version 330 core

#include <assets/lib/std/incl/lighting.glsl>

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;

out vec3 normal;
out vec3 fragPos;
out vec2 uv;

uniform mat4 u_modelMat;
uniform mat4 u_viewMat;
uniform mat4 u_projMat;


void main()
{
	gl_Position = u_projMat * u_viewMat * u_modelMat * vec4(a_position, 1.0);
	fragPos = vec3(u_modelMat * vec4(a_position, 1.0));
	normal = mat3(transpose(inverse(u_modelMat))) * a_normal;  
        uv = a_uv;
}

