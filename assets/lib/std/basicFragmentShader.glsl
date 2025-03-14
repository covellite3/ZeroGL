#version 330 core
#include <assets/lib/std/incl/lighting.glsl>

in vec2 v_uv;
in vec3 v_normal;
in vec3 v_camDirection;
in vec3 v_directionLight;

out vec3 FragColor;


//uniform vec3 u_camPos;
uniform sampler2D u_tex;
uniform vec3 u_colorLight;

/** Put vector between [-1;1] into color space between [0;1] */
vec3 colorifyVector(vec3 v)
{
	return (v + vec3(1.0))/2;
}

void main() {
	//vec3 viewDir = normalize(viewPos - FragPos);
	float diff = max(0, dot(normalize(v_normal), -v_directionLight));
	vec4 texColor = texture(u_tex, v_uv);
	FragColor = vec3(diff * texColor);
	//FragColor = colorify(v_normal);
}

