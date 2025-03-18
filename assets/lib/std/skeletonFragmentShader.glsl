#version 330 core
//#include <assets/lib/std/incl/lighting.glsl>

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


vec3 mixBoneColors(vec3 weights, ivec3 boneIndices)
{
	// Define 5 contrasting colors
	vec3 colors[5];
	colors[0] = vec3(1.0, 0.0, 0.0); // Red
	colors[1] = vec3(0.0, 1.0, 0.0); // Green
	colors[2] = vec3(0.0, 0.0, 1.0); // Blue
	colors[3] = vec3(1.0, 1.0, 0.0); // Yellow
	colors[4] = vec3(1.0, 0.5, 0.0); // Orange

	// Normalize the weights to ensure they sum to 1
	float totalWeight = weights.x + weights.y + weights.z;
	if (totalWeight > 0.0)
	{
		weights /= totalWeight; // Normalize weights
	}

	// Fetch the colors based on the bone indices
	vec3 color1 = colors[boneIndices.x % 5];
	vec3 color2 = colors[boneIndices.y % 5];
	vec3 color3 = colors[boneIndices.z % 5];

	// Blend the colors based on the normalized weights
	return color1 * weights.x + color2 * weights.y + color3 * weights.z;
}


void main() {
	//FragColor = vec3(v_weights);
	FragColor = mixBoneColors(v_weights, v_boneIndices);
}

