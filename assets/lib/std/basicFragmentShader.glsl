#version 330 core

#include <assets/lib/std/incl/lighting.glsl>

in vec3 normal;
in vec3 fragPos;
in vec2 uv;

out vec4 FragColor;

uniform vec3 u_lightVector;
uniform sampler2D u_tex;


void main()
{

	float ambient = 0.3f;
	vec3 lightColor = vec3(1.0);
	vec3 normalizedNormal = normalize(normal);
	//vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(normalizedNormal, -u_lightVector), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 texColor = texture(u_tex, vec2(uv.x , 1.0-uv.y)).xyz;
	vec3 result = (ambient + diffuse) * texColor;
	FragColor = vec4(result, 1.0);
}


