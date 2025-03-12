#version 330 core
#include <assets/lib/std/incl/lighting.glsl>

in vec2 v_uv;
in vec3 v_normal;
in vec3 v_cam_direction;
in vec3 v_cam_pos;
in vec3 v_lightVector;

out vec3 FragColor;

uniform sampler2D u_tex;

void main() {
	// Basic lighting calculation
	vec3 lightDir = normalize(v_lightVector);
	float diff = max(dot(v_normal, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1.0, 1.0, 1.0); 

	// Ambient lighting
	vec3 ambient = 0.1 * vec3(1.0, 1.0, 1.0);

	// View direction
	vec3 viewDir = normalize(v_cam_direction);
	
	// Combine texture and lighting
	vec4 texColor = texture(u_tex, v_uv);
	FragColor = texColor.rgb * (ambient + diffuse);
}

