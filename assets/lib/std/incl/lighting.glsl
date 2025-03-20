/**
 * Lighting include for shaders.
 */

#define PI 3.14159265359

struct Light {
	vec3 direction;
	vec3 color;
};

struct Camera {
	vec3 position;
	vec3 direction;
};

struct Material {
	vec3 normal;
	float shininess;
	float metallic;
	float IOR;
	float roughness;
 	vec3 baseColor;
};

/** Shadow mappin */
float shadowmapping(sampler2D shadowmap, vec3 normal, vec3 directionLight, vec4 lightFragPos, float minimumBias, float paramBias, int radius)
{
	// Shadowmap 
	float shadowness = 0.0f; // How much in the shadow
	vec2 shadowMapPixelSize = 1.0 / textureSize(shadowmap, 0);
	vec3 clipLightFragPos = lightFragPos.xyz / lightFragPos.w; // clip space
	if(	clipLightFragPos.z <=  1.0f &&
		clipLightFragPos.x <=  1.0f &&
		clipLightFragPos.y <=  1.0f &&
		clipLightFragPos.z >= -1.0f &&
		clipLightFragPos.x >= -1.0f &&
		clipLightFragPos.y >= -1.0f) {
		// Inside the frustrum of the shadowmap's camera
		vec3 shadowMapFragPos = (clipLightFragPos + 1.0f) / 2.0f; // Shift to range [0;1]
		float bias = max(paramBias * (1.0f - dot(normal, directionLight)), minimumBias);
		// Soft shadow
		for(int y = -radius; y <= radius; ++y)
		{
			for(int x = -radius; x <= radius; ++x)
			{
				float shadowMapDepth = texture(shadowmap, shadowMapFragPos.xy + vec2(x, y)*shadowMapPixelSize).r;
				if(shadowMapFragPos.z > shadowMapDepth + bias) {
					shadowness += 1.0f;
				}

			}
		}
		shadowness /= pow((radius*2 + 1), 2);
	}
	return shadowness;
}


///
///
///
///
///



void blinnPhong(Camera camera, Light light, Material material, out float diffuse, out float specular)
{
	diffuse = max(0.0f, dot(material.normal, light.direction));
	specular = 0.0f;
	if (diffuse >= 0.0f) {
		vec3 halfvec = normalize(camera.direction + light.direction);
		specular = pow(max(0.0f, dot(material.normal, halfvec)), material.shininess);
	}
}




///
///
///
///
///


float chiplus(float c) {
	return (c > 0.0) ? 1.0 : 0.0;
}

float specular_brdf(Camera cam, Light light, Material material)
{
	vec3 n = material.normal;
	vec3 v = cam.direction;
	vec3 l = light.direction;
	vec3 lc = light.color; 
	vec3 h = normalize(v + l);

	float NdotL = dot(n, l);
	float HdotL = dot(h, l);
	float HdotV = dot(h, v);
	float NdotV = dot(n, v);
	float alphaSquare = pow(material.roughness, 4);

	float V =
		chiplus(HdotL) /
		(abs(NdotL)+sqrt(alphaSquare+(1-alphaSquare)*NdotL*NdotL));

	float D =
		chiplus(HdotV) /
		(abs(NdotV)+sqrt(alphaSquare+(1-alphaSquare)*NdotV*NdotV));



	return V*D;
}


vec3 diffuse_brdf(vec3 color)
{
	return (1/PI) * color;
}

float conductor_fresnel(float f0, float bsdf, float VdotH)
{
	return bsdf * (f0 + (1 - f0) * pow(1 - abs(VdotH), 5));
}

float fresnel_mix(float ior, float base, float layer, float VdotH) {
	float f0 = pow((1-ior)/(1+ior), 2);
	float fr = f0 + (1 - f0)*pow(1 - abs(VdotH), 5);
	return mix(base, layer, fr);
}

vec3 brdf(Camera cam, Light light, Material material)
{
	vec3 n = material.normal;
	vec3 v = cam.direction;
	vec3 l = light.direction;
	vec3 lc = light.color; 
	vec3 h = normalize(v + l);
	float VdotH = dot(v, h);

	vec3 metal_brdf = specular_brdf(cam, light, material) * (material.baseColor.rgb + (1 - material.baseColor.rgb) * pow(1 - abs(VdotH),5));

	vec3 dielectric_brdf = mix(
		diffuse_brdf(material.baseColor.rgb),
		vec3(specular_brdf(cam, light, material)),
		0.04 + (1 - 0.04) * pow(1 - abs(VdotH), 5)
	);

	return mix(dielectric_brdf, metal_brdf, material.metallic);
}
