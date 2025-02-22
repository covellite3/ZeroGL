#version 330 core

in vec3 normal;
in vec2 uv;

out vec4 FragColor;

uniform vec3 u_lightVector;
uniform sampler2D u_tex;

void main()
{
	float ambiant = 0.3f;
        float lum = 0;
	lum = max(dot(-u_lightVector, normal), ambiant);
	vec3 color = texture(u_tex, vec2(uv.x , 1.0-uv.y)).xyz;
        //FragColor = vec4(color*lum, 1.0f);
        //FragColor = vec4(vec3(uv, 1.0f)*lum, 1.0f);
        //FragColor = vec4(vec3(normal)*lum, 1.0f);
        FragColor = vec4(vec3(1.0f), 1.0f);
}


