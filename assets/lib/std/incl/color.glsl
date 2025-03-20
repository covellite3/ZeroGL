vec3 mixBoneColors(vec3 weights, ivec3 boneIndices)
{
	// TODO use HSV color space for interpolation

	// Define 5 contrasting colors
	vec3 colors[5];
	colors[0] = vec3(1.0, 0.0, 0.0); // Red
	colors[1] = vec3(0.0, 1.0, 0.0); // Green
	colors[2] = vec3(0.0, 0.0, 1.0); // Blue
	colors[3] = vec3(1.0, 1.0, 0.0); // Yellow
	colors[4] = vec3(1.0, 0.5, 0.0); // Orange

	// Normalize the weights to ensure they sum to 1
	float totalWeight = weights.x + weights.y + weights.z;
	if (totalWeight > 0.0)
	{
		weights /= totalWeight; // Normalize weights
	}

	// Fetch the colors based on the bone indices
	vec3 color1 = colors[boneIndices.x % 5];
	vec3 color2 = colors[boneIndices.y % 5];
	vec3 color3 = colors[boneIndices.z % 5];

	// Blend the colors based on the normalized weights
	return color1 * weights.x + color2 * weights.y + color3 * weights.z;
}

float linearizeDepth(float depth, float zNear, float zFar)
{
	depth = (2.0f * zNear) / (zFar + zNear - depth * (zFar - zNear));
	return depth;
}

/** Put vector between [-1;1] into color space between [0;1] */
vec3 colorifyVector(vec3 v)
{
	return (v + vec3(1.0f))/2;
}
