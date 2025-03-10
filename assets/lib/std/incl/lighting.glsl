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
 * Struct of directional light, no position, all ray parallele.
 */
struct SunLight {
	float ambiant;
	vec3 color;
	vec3 direction;
	//sample2D sunView;
};

/**
 * Struct of one point of light, emite in all direction, weakening with distance.
 */
struct TorchLight {
	float ambiant;
	vec3 color;
	vec3 pos;
};

/**
 * Struct of the shinness dampness and normal of surface material
 */
struct SurfaceMaterial {
	float scatterness;
	float shinness;
	vec3 normal;
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
SunLight getSunLight(float ambiant, vec3 color, vec3 direction) {
	SunLight light;
	light.ambiant = ambiant;
	light.color = color;
	light.direction = direction;
	return light;
}

/**
 * Constructor SurfaceMaterial.
 */
 SurfaceMaterial getSurfaceMaterial(float scatterness, float shinness, vec3 normal) {
 	SurfaceMaterial surface;
 	surface.scatterness = scatterness;
 	surface.shinness = shinness;
 	surface.normal = normal;
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
float getPhongLighting(Camera cam, SunLight light, SurfaceMaterial surface) {
	// Diffuse
	float diffuseFactor = dot(light.direction, -surface.normal) * surface.scatterness;

	// Specular
	vec3 reflectedDirectionalLight = reflect(light.direction, surface.normal);
	float specularFactor = dot(cam.direction, -reflectedDirectionalLight) * surface.shinness;

	// Total
	return light.ambiant + diffuseFactor + specularFactor;
}

/**
 * Get normal from texture's rgb value.
 */
 vec3 getNormalFromRGB(vec3 color) {
 	return color.xyz * 2.0 - 1.0;
 }