#version 330 core
#include <assets/lib/std/incl/lighting.glsl>

in vec2 v_uv;
in vec3 v_normal;
//in vec3 v_directionCamera;
in vec3 v_directionLight;
in vec3 v_fragPos;

out vec3 FragColor;


//uniform vec3 u_camPos;
uniform sampler2D u_tex;
uniform vec3 u_colorLight;
uniform vec3 u_positionCamera;

/** Put vector between [-1;1] into color space between [0;1] */
vec3 colorifyVector(vec3 v)
{
	return (v + vec3(1.0f))/2;
}

void main() {
	// Material
	vec4 texColor = texture(u_tex, v_uv);
	float ambient = 0.1f;
	float shininess = 20.f;

	// Blinn-Phong lighting
	float diffuse = max(0.0f, dot(v_normal, v_directionLight));
	float specular = 0.0f;
	if(diffuse >= 0.0f) {
		vec3 viewDirection = normalize(u_positionCamera - v_fragPos);
		vec3 reflectedLight = reflect(v_directionLight, v_normal);
		vec3 halfvec = normalize(viewDirection + v_directionLight);
		specular = pow(max(0.0f, dot(v_normal, halfvec)), shininess);
	}
	float totalLighting = ambient + diffuse + specular;

	// Fragment's color
	//FragColor = vec3(totalLighting * texColor);
	FragColor = vec3(v_uv, 1.0);
}

