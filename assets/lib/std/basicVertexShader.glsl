#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;

out vec3 normal;
out vec2 uv;

uniform mat4 u_modelMat;
uniform mat4 u_viewMat;
uniform mat4 u_projMat;

void main()
{
        mat4 modelViewMat = u_viewMat * u_modelMat;
        mat4 modelViewProjMat = u_projMat * modelViewMat;
	mat4 normalMat = transpose(inverse(modelViewMat));
        normal = (normalMat*vec4(a_normal, 1.0f)).xyz;
        uv = a_uv;
        gl_Position = modelViewProjMat * vec4(a_position, 1.0f);
        //gl_Position = vec4(a_position, 1.0f);
}

