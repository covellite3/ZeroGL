/**
 * Lighting include for shaders.
 */

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


void blinnPhong(float shininess, vec3 normal, vec3 directionLight, vec3 positionCamera, vec3 fragPos, out float diffuse, out float specular)
{
	// Blinn-Phong lighting
	diffuse = max(0.0f, dot(normal, directionLight));
	specular = 0.0f;
	if(diffuse >= 0.0f) {
		vec3 viewDirection = normalize(positionCamera - fragPos);
		vec3 reflectedLight = reflect(directionLight, normal);
		vec3 halfvec = normalize(viewDirection + directionLight);
		specular = pow(max(0.0f, dot(normal, halfvec)), shininess);
	}
}



///
///
///
///
///


float RDM_chiplus(float c) {
	return (c > 0.0) ? 1.0 : 0.0;
}

float RDM_Beckmann(float NdotH, float alpha) {
	float cos2h = pow(NdotH, 2.0);
	float cos4h = pow(cos2h, 2.0);
	float tan2h = (1.0 - cos2h) / cos2h;
	float alpha2 = alpha * alpha;
	return RDM_chiplus(NdotH) * (exp(-tan2h / alpha2) / (3.14159265359 * alpha2 * cos4h));
}

float RDM_Fresnel(float LdotH, float extIOR, float intIOR) {
	float n1_cos_theta_i = extIOR * LdotH;
	float n2_cos_theta_i = intIOR * LdotH;

	float sin2_theta_t = pow(extIOR / intIOR, 2.0) * (1.0 - LdotH * LdotH);
	if (sin2_theta_t > 1.0) {
		return 1.0; // Total internal reflection
	}

	float cos_theta_t = sqrt(1.0 - sin2_theta_t);
	float n1_cos_theta_t = extIOR * cos_theta_t;
	float n2_cos_theta_t = intIOR * cos_theta_t;

	float Rs = pow(n1_cos_theta_i - n2_cos_theta_t, 2.0) / pow(n1_cos_theta_i + n2_cos_theta_t, 2.0);
	float Rp = pow(n1_cos_theta_t - n2_cos_theta_i, 2.0) / pow(n1_cos_theta_t + n2_cos_theta_i, 2.0);

	return 0.5 * (Rs + Rp);
}

float RDM_G1(float DdotH, float DdotN, float alpha) {
	float k = DdotH / DdotN;
	float cos_theta_x = DdotN;
	float tan_theta_x = sqrt(1.0 - cos_theta_x * cos_theta_x) / cos_theta_x;
	float b = 1.0 / (alpha * tan_theta_x);

	float bb = b * b;
	if (b < 1.6) {
		return RDM_chiplus(k) * ((3.535 * b + 2.181 * bb) / (1.0 + 2.276 * b + 2.577 * bb));
	} else {
		return RDM_chiplus(k);
	}
}

float RDM_Smith(float LdotH, float LdotN, float VdotH, float VdotN, float alpha) {
	return RDM_G1(LdotH, LdotN, alpha) * RDM_G1(VdotH, VdotN, alpha);
}

vec3 RDM_bsdf_s(float LdotH, float NdotH, float VdotH, float LdotN, float VdotN, float roughness, float IOR, vec3 specular) {
	float extIOR = 1.0;
	float intIOR = IOR;
	float D = RDM_Beckmann(NdotH, roughness);
	float F = RDM_Fresnel(LdotH, extIOR, intIOR);
	float G = RDM_Smith(LdotH, LdotN, VdotH, VdotN, roughness);
	return specular * ((D * F * G) / (4.0 * LdotN * VdotN));
}

vec3 RDM_bsdf_d(vec3 diffuse) {
	return diffuse / 3.14159265359;
}

vec3 RDM_bsdf(float LdotH, float NdotH, float VdotH, float LdotN, float VdotN, float roughness, float IOR, vec3 specular, vec3 diffuse) {
	vec3 bsdf_s = vec3(0.0);
	if (VdotN > 0.0 && LdotN > 0.0) {
		bsdf_s = RDM_bsdf_s(LdotH, NdotH, VdotH, LdotN, VdotN, roughness, IOR, specular);
	}

	vec3 bsdf_d = RDM_bsdf_d(diffuse);
	return bsdf_d + bsdf_s;
}

/**
 * Get RDM Lighting based on Cook-Torrance model.
 */
/*vec3 getRDM_Lighting(Camera cam, Light light, RDM_Material material) {
	// TODO rewrite this
	vec3 n = material.normal;
	vec3 v = cam.direction;
	vec3 l = light.direction;
	vec3 lc = light.color; 
	vec3 h = normalize(v + l);

	const float eps = 0.00000001;

	float LdotH = max(dot(l, h), eps);
	float NdotH = max(dot(n, h), eps);
	float VdotH = max(dot(v, h), eps);
	float LdotN = max(dot(l, n), eps);
	float VdotN = max(dot(v, n), eps);

	vec3 bsdf = RDM_bsdf(LdotH, NdotH, VdotH, LdotN, VdotN, material.roughness, material.IOR, material.specularColor, material.diffuseColor);
	return clamp(lc * bsdf * LdotN, 0.0, 1.0);
}*/



