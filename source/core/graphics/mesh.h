#pragma once

typedef float32* VertData;
typedef uint32* IndexData;
typedef uint32 Index;

struct VertexP3C3
{
	float32 postion[3];
	float32 color[3];
};

struct StaticMesh
{
	VertData	vertices;
	IndexData	indices;
};