#version 330 core

//#include <assets/lib/std/incl/lighting.glsl>
#include <assets/lib/std/incl/color.glsl>

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


	// Blinn-Phong lighting
	vec3 directionLight;
	float intensity;
	if(isSunLight) {
		directionLight = u_directionLight;
		intensity = 1.0;
	} else {
		vec3 unormalizedDirectionLight = u_coordLight - v_fragPos;
		float distFragmentToLight = length(unormalizedDirectionLight);
		directionLight = unormalizedDirectionLight/distFragmentToLight;
		intensity = 1.0f/( a*distFragmentToLight*distFragmentToLight + b*distFragmentToLight + 1.0f);
	}
	float diffuse = max(0.0f, dot(v_normal, directionLight));
	float specular = 0.0f;
	if(diffuse >= 0.0f) {
		vec3 viewDirection = normalize(u_positionCamera - v_fragPos);
		vec3 reflectedLight = reflect(directionLight, v_normal);
		vec3 halfvec = normalize(viewDirection + directionLight);
		specular = pow(max(0.0f, dot(v_normal, halfvec)), shininess);
	}

	// Shadowmap 
	float shadowness = 0.0f; // How much in the shadow
	vec2 shadowMapPixelSize = 1.0 / textureSize(u_shadowmap, 0);
	vec3 clipLightFragPos = v_lightFragPos.xyz / v_lightFragPos.w; // clip space
	if(	clipLightFragPos.z <=  1.0f &&
		clipLightFragPos.x <=  1.0f &&
		clipLightFragPos.y <=  1.0f &&
		clipLightFragPos.z >= -1.0f &&
		clipLightFragPos.x >= -1.0f &&
		clipLightFragPos.y >= -1.0f) {
		// Inside the frustrum of the shadowmap's camera
		vec3 shadowMapFragPos = (clipLightFragPos + 1.0f) / 2.0f; // Shift to range [0;1]
		float bias = max(paramBias * (1.0f - dot(v_normal, directionLight)), minimumBias);
		// Soft shadow
		for(int y = -radius; y <= radius; ++y)
		{
			for(int x = -radius; x <= radius; ++x)
			{
				float shadowMapDepth = texture(u_shadowmap, shadowMapFragPos.xy + vec2(x, y)*shadowMapPixelSize).r;
				if(shadowMapFragPos.z > shadowMapDepth + bias) {
					shadowness += 1.0f;
				}

			}
		}
		shadowness /= pow((radius*2 + 1), 2);
	}

	//float totalLighting = (ambient + diffuse + specular)*intensity;
	//float totalLighting = (ambient + diffuse + specular)*intensity*(1.0f-shadowness);
	float totalLighting = max(ambient, (diffuse + specular)*intensity*(1.0f-shadowness));

	// Fragment's color
	//FragColor = vec3(totalLighting * texColor);
	FragColor = vec3(totalLighting * texColor);
	//FragColor = vec3(v_uv, 1.0f);
	//FragColor = vec3(shadowness);
	//FragColor = colorifyVector(v_normal);
}

