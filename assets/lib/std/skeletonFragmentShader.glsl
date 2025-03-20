#version 330 core

//#include <assets/lib/std/incl/lighting.glsl>
#include <assets/lib/std/incl/color.glsl>

in vec2 v_uv;
in vec3 v_normal;
in vec3 v_weights;
flat in ivec3 v_boneIndices;
in vec3 v_fragPos;
in vec4 v_lightFragPos;

out vec3 FragColor;

uniform sampler2D u_tex;
uniform sampler2D u_shadowmap;
uniform vec3 u_positionCamera;
uniform vec3 u_colorLight;
uniform vec3 u_coordLight;
uniform vec3 u_directionLight;
uniform float u_zNearLight;
uniform float u_zFarLight;

void main() {
	//FragColor = sqrt(v_weights);
	//FragColor = v_weights;
	FragColor = mixBoneColors(v_weights, v_boneIndices);
	//FragColor = colorifyVector(v_normal);
}

