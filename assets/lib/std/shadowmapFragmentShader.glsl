#version 330 core
//#include <assets/lib/std/incl/lighting.glsl>

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

float linearizeDepth(float depth, float zNear, float zFar)
{
	depth = (2.0f * zNear) / (zFar + zNear - depth * (zFar - zNear));
	return depth;
}

void main() {
	// Material
	FragColor = vec3(50*linearizeDepth(gl_FragCoord.z, u_zNearLight, u_zFarLight));

}

