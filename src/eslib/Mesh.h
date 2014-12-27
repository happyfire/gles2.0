#ifndef ESL_MESH_H
#define ESL_MESH_H

#include "BaseObject.h"
#include "sharedPtr.h"
#include "glcommon.h"
#include "esUtil/esUtil.h"

NS_ESLIB_BEGIN

ESL_FORWARD_PTR(Mesh)
ESL_FORWARD_PTR(Material)
ESL_FORWARD_PTR(Geometry)

class Matrix4;

enum EMeshVertexFlag
{
	MVF_POS_3F = 1,
	MVF_TCOORD_2F = 1<<1,
};

class Mesh: public BaseObject
{
public:
	Mesh();
	virtual ~Mesh();

	GeometryPtr createEmpty(int vertexFlag, int vertexCount, int indexCount, bool useVBO=true, bool multiStream=false);
    
    GeometryPtr createDebugBox();
    
	void setMaterial(const MaterialPtr& material);

	void setTransform(const Matrix4 &transform);

	void render();

	const MaterialPtr& getMaterial() { return m_material; }
    
    const GeometryPtr& getGeometry() { return m_geometry; }

protected:
	MaterialPtr m_material;
	GeometryPtr m_geometry;
};



NS_ESLIB_END

#endif //ESL_SHADER_H