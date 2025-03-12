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


	// Get texture color
	vec3 texColor = texture2D(u_tex, vec2(v_uv.x, 1.0 - v_uv.y)).rgb;

	// Declaring structs
	Camera cam = getCamera(v_cam_pos, v_cam_direction);
	Light light = getLight(0.0, vec3(1.0), v_lightVector);
	PhongMaterial surface = getPhongMaterial(1.0, 0.3, v_normal, texColor, texColor, texColor);
	//RDM_Material surface = getRDM_Material(10.5, 0.99, v_normal, texColor, texColor, texColor);

	// Calculate lighting
	vec3 lighting = getPhongLighting(cam, light, surface);
	//vec3 lighting = getRDM_Lighting(cam, sunLight, surface);
	FragColor = lighting;
	FragColor = v_normal;

}
