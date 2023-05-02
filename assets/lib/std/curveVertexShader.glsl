#version 330 core

layout (location = 0) in vec3 a_position;

uniform mat4 u_modelMat;
uniform mat4 u_viewMat;
uniform mat4 u_projMat;

void main()
{
        mat4 modelViewProjMat = u_projMat * u_viewMat * u_modelMat;
        gl_Position = modelViewProjMat * vec4(a_position, 1.0f);
}

