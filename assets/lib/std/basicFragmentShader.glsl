#version 330 core
#include <assets/lib/std/incl/lighting.glsl>

in vec2 v_uv;
in vec3 v_normal;
in vec3 v_fragPos;

out vec3 FragColor;

uniform sampler2D u_tex;
uniform sampler2D u_shadowmap;
uniform vec3 u_positionCamera;
uniform vec3 u_colorLight;
uniform vec3 u_coordLight;
uniform vec3 u_directionLight;
uniform float u_zNearLight;
uniform float u_zFarLight;

/** Put vector between [-1;1] into color space between [0;1] */
vec3 colorifyVector(vec3 v)
{
	return (v + vec3(1.0f))/2;
}

float linearizeDepth(sampler2D depthBuffer, vec2 uv, float zNear, float zFar)
{
	float depth = texture(depthBuffer, uv).x;
	depth = (2.0f * zNear) / (zFar + zNear - depth * (zFar - zNear));
	return depth;
}

void main() {
	// Material
	//vec4 texColor = texture(u_tex, v_uv);
	vec4 texColor = vec4(sqrt(linearizeDepth(u_shadowmap, v_uv, u_zNearLight, u_zFarLight)));
	float ambient = 0.1f;
	float shininess = 20.f;
	float a = 0.05;
	float b = 0.005;
	// Blinn-Phong lighting
	bool isSunLight = true;
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

	float totalLighting = (ambient + diffuse + specular)*intensity;
	//float totalLighting = intensity;

	// Fragment's color
	FragColor = vec3(totalLighting * texColor);
	//FragColor = vec3(v_uv, 1.0f);
}

