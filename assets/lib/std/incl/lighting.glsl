/**
 * Lighting include for shaders.
 */

/**
 * Struct of the camera.
 */
struct Camera {
	vec3 pos;
	vec3 direction;
};

/**
 * Struct of one point of light, emite in all direction, weakening with distance.
 */
struct Light {
	float ambient;
	vec3 color;
	vec3 direction;
};

/**
 * Struct of the shinness dampness and normal of surface material
 */
struct PhongMaterial {
	float scatterness;
	float shinness;
	vec3 normal;
	vec3 ambientColor; 
	vec3 diffuseColor;
	vec3 specularColor;
};

/**
 * Constructor Camera.
 */
Camera getCamera(vec3 pos, vec3 direction) {
	Camera cam;
	cam.pos = pos;
	cam.direction = direction;
	return cam;
}

/**
 * Constructor SunLight.
 */
Light getLight(float ambient, vec3 color, vec3 direction) {
	Light light;
	light.ambient = ambient;
	light.color = color;
	light.direction = direction;
	return light;
}

/**
 * Constructor Phong's SurfaceMaterial.
 */
 PhongMaterial getPhongMaterial(float scatterness, float shinness, vec3 normal, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor) {
 	PhongMaterial surface;
 	surface.scatterness = scatterness;
 	surface.shinness = shinness;
 	surface.normal = normal;
	surface.ambientColor = ambientColor;
	surface.diffuseColor = diffuseColor;
	surface.specularColor = specularColor;
 	return surface;
 }



/**
 * Get pos from view matrix.
 */
vec3 getPosFromView(mat4 viewMat) {
	return -viewMat[3].xyz;
}

/**
 * Get direction from view matrix.
 */
vec3 getDirectionFromView(mat4 viewMat) {
	return -transpose(viewMat)[2].xyz;
}

/**
 * Get Phong's lighting.
 */

vec3 getPhongLighting(Camera cam, Light light, PhongMaterial surface) {
	// Normalize camera direction to ensure correct calculation
	vec3 normalizedCamDirection = normalize(cam.direction);

	// Diffuse
	float diffuseFactor = max(dot(-light.direction, surface.normal), 0.0f) * surface.scatterness;

	// Specular
	vec3 reflectedDirectionalLight = reflect(-light.direction, surface.normal);
	float specularFactor = pow(max(dot(normalizedCamDirection, reflectedDirectionalLight), 0.0f), surface.shinness);

	// Ambient
	vec3 ambientColor = surface.ambientColor * light.ambient;

	// Diffuse + Specular components
	vec3 diffuseColor = diffuseFactor * surface.diffuseColor * light.color;  // Mixing diffuse component
	vec3 specularColor = specularFactor * surface.specularColor * light.color;  // Mixing specular component

	// Return the final color
	return max(ambientColor, min(diffuseColor + specularColor, vec3(1.0)));
}




/**
 * Get normal from texture's rgb value.
 */
 vec3 getNormalFromRGB(vec3 color) {
 	return color.xyz * 2.0 - 1.0;
 }

//
// Rough Dielectric Material
//

/**
 * TODO
 */
struct RDM_Material {
	float roughness;
	float IOR;
	vec3 normal;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};

/**
 * Constructor for RDM_Material.
 */
RDM_Material getRDM_Material(float roughness, float IOR, vec3 normal, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor) {
	RDM_Material material;
	material.roughness = roughness;
	material.IOR = IOR;
	material.normal = normal;
	material.ambientColor = ambientColor;
	material.diffuseColor = diffuseColor;
	material.specularColor = specularColor;
	return material;
}

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
vec3 getRDM_Lighting(Camera cam, Light light, RDM_Material material) {
	// TODO rewrite this
	vec3 n = material.normal;
	vec3 v = -cam.direction;
	vec3 l = -light.direction;
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
}


//
// Shadow map
//

/*bool isInShadown(sampler2D shadowMap, mat4 lightWorldViewProjectionMat, lightSpacePosition)
{
	return false; 
}*/
