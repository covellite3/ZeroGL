#version 330 core
//#include <assets/lib/std/incl/lighting.glsl>

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;

out vec2 v_uv;
out vec3 v_normal;
out vec3 v_fragPos;
out vec4 v_lightFragPos;

uniform mat4 u_modelMat;
uniform mat4 u_viewMat;
uniform mat4 u_projMat;
uniform mat4 u_lightProjMat;

void main()
{
	v_fragPos = vec3(u_modelMat * vec4(a_position, 1.0f));
	gl_Position = u_projMat * u_viewMat * vec4(v_fragPos, 1.0f);
	v_lightFragPos = u_lightProjMat * vec4(v_fragPos, 1.0f);
	v_normal = normalize(mat3(transpose(inverse(u_modelMat))) * a_normal);
	//v_uv = vec2(a_uv.x, 1.0 - a_uv.y);
	v_uv = a_uv;
}



