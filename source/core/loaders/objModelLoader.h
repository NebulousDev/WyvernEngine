#pragma once

#include <vector>	//TODO: Convert to custom array
#include "../math/vector.h"

struct OBJMaterial
{
	const char*		name;
	const Vec3f		alpha;
	const Vec3f		diffuse;
	const Vec3f		specular;
	const float32	exponent;
	const Vec3f		emmision;
	const float32	refraction;
	const float32	opaqueness;
	const uint32	illum;

	const char*		diffuseMap;
	const char*		specularMap;
	const char*		bumpMap;
};

struct OBJVertex
{
	Vec3f	position;
	Vec3f	normal;
	Vec2f	texCoord;
	uint32	material;
};

struct OBJMesh
{
	const char*					name;
	std::vector<OBJVertex>		vertices;
	std::vector<uint32>			indices;
	std::vector<OBJMaterial>	materials;
};

struct OBJModel
{
	const char* name;
	std::vector<OBJMesh> meshes;
};
