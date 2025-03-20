#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;
layout (location = 3) in vec3 a_weights;
layout (location = 4) in ivec3 a_boneIndices;

out vec2 v_uv;
out vec3 v_normal;
out vec3 v_weights;
flat out ivec3 v_boneIndices;
out vec3 v_fragPos;
out vec4 v_lightFragPos;

uniform mat4 u_modelMat;
uniform mat4 u_viewMat;
uniform mat4 u_projMat;
uniform mat4 u_lightProjMat;

uniform mat4 u_bones[128];

void main()
{
	mat4 boneTransform =
		a_weights.x * u_bones[a_boneIndices.x] +
		a_weights.y * u_bones[a_boneIndices.y] +
		a_weights.z * u_bones[a_boneIndices.z];

	vec4 transformedPosition = boneTransform * vec4(a_position, 1.0);

	v_fragPos = vec3(u_modelMat * transformedPosition);

	gl_Position = u_projMat * u_viewMat * vec4(v_fragPos, 1.0);

	v_lightFragPos = u_lightProjMat * vec4(v_fragPos, 1.0);

	//v_normal = normalize(mat3(transpose(inverse(u_modelMat))) * mat3(boneTransform) * a_normal);
	v_normal = normalize(mat3(transpose(inverse(u_modelMat*boneTransform))) * a_normal);

	v_uv = a_uv;
	v_weights = a_weights;
	v_boneIndices = a_boneIndices;
}

