#ifndef MD2_MESH_LOADER
#define MD2_MESH_LOADER

#include "eslib/common.h"
#include "eslib/Mesh.h"

class MD2MeshLoader
{
public:
	MD2MeshLoader();
	eslib::MeshPtr load(const char* md2File, const char* textureFile);
};

#endif