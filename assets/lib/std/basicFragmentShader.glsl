#version 330 core

#include <assets/lib/std/incl/lighting.glsl>
//#include <assets/lib/std/incl/color.glsl>

in vec2 v_uv;
in vec3 v_normal;
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

	// Params light
	float ambient = 0.1f;
	bool isSunLight = true; // Is matrix othro and parallel rays
	float paramBias = 0.000025f; // Adaptative bias
	float minimumBias = 0.00005f; // Minimum bias
	int radius = 2;// Soft shadow
	float a = 0.05; // Phong
	float b = 0.005; // Phong

	// Param Material
	vec4 texColor = texture(u_tex, v_uv);
	float shininess = 20.f;

	vec3 directionLight;
	float intensity;
	if(isSunLight) {
		// Sun light (ortho)
		directionLight = u_directionLight;
		intensity = 1.0;
	} else {
		// Point light
		vec3 unormalizedDirectionLight = u_coordLight - v_fragPos;
		float distFragmentToLight = length(unormalizedDirectionLight);
		directionLight = unormalizedDirectionLight/distFragmentToLight;
		intensity = 1.0f/( a*distFragmentToLight*distFragmentToLight + b*distFragmentToLight + 1.0f);
	}

	float diffuse, specular;
	blinnPhong(shininess, v_normal, directionLight, u_positionCamera, v_fragPos, diffuse, specular);
	float shadowness = shadowmapping(u_shadowmap, v_normal, directionLight, v_lightFragPos, minimumBias, paramBias, radius);
	float totalLighting = max(ambient, (diffuse + specular)*intensity*(1.0f-shadowness));

	FragColor = vec3(totalLighting * texColor);
}

