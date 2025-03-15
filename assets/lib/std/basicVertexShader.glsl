#version 330 core
#include <assets/lib/std/incl/lighting.glsl>

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;

out vec2 v_uv;
out vec3 v_normal;
out vec3 v_fragPos;

uniform mat4 u_modelMat;
uniform mat4 u_viewMat;
uniform mat4 u_projMat;

void main()
{
	//v_positionCamera = vec3(u_modelMat * vec4(u_positionCamera, 1.0f));
	v_fragPos = vec3(u_modelMat * vec4(a_position, 1.0f));
	gl_Position = u_projMat * u_viewMat * vec4(v_fragPos, 1.0f);
	v_uv = a_uv;
	v_normal = mat3(transpose(inverse(u_modelMat))) * a_normal; // TODO verify this line
}



