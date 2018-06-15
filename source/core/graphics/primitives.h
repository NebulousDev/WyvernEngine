#pragma once

#include "../common.h"
#include "mesh.h"

#define LOCAL static

LOCAL VertexP3C3 sPlaneVertsIP3C3[] =
{
	{{-0.5, -0.5, 0.0}, {1.0, 1.0, 1.0}},
	{{-0.5,  0.5, 0.0}, {1.0, 1.0, 1.0}},
	{{ 0.5,  0.5, 0.0}, {1.0, 1.0, 1.0}},
	{{ 0.5, -0.5, 0.0}, {1.0, 1.0, 1.0}},
};

LOCAL Index sPlaneIdxsIP3C3[] = 
	{ 0, 1, 2, 0, 3, 2 };
	
StaticMesh sPlaneIP3C3 = 
	{ (float32*)sPlaneVertsIP3C3, (uint32*)sPlaneIdxsIP3C3 };


