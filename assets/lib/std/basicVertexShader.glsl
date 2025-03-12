#version 330 core
#include <assets/lib/std/incl/lighting.glsl>

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;

out vec2 v_uv;
out vec3 v_normal;
out vec3 v_cam_direction;
out vec3 v_cam_pos;
out vec3 v_lightVector;

uniform mat4 u_modelMat;
uniform mat4 u_viewMat;
uniform mat4 u_projMat;

uniform vec3 u_pointLight;


void main()
{
	v_uv = a_uv;
	v_normal = mat3(transpose(inverse(u_modelMat))) * a_normal;  
	v_cam_direction = getDirectionFromView(u_viewMat);
	v_cam_pos = getPosFromView(u_viewMat);

	gl_Position.xyzw = u_projMat * u_viewMat * u_modelMat * vec4(a_position.xyz, 1.0);
	vec3 FragPos = vec3(u_modelMat * vec4(a_position, 1.0));
	v_lightVector = normalize(u_pointLight - FragPos);  
}


