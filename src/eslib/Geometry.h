#ifndef ESL_GEOMETRY_H
#define ESL_GEOMETRY_H

#include "BaseObject.h"
#include "sharedPtr.h"
#include "glcommon.h"
#include <vector>


NS_ESLIB_BEGIN

ESL_FORWARD_PTR(ShaderProgram)
ESL_FORWARD_PTR(Geometry)

//Shader class, vertex or fragment shader

struct VertexAttribute
{
	int ElementCount;
	int offset; //offset in float
	int Location;
	std::string Name; //Name in shader

	VertexAttribute()
		:ElementCount(0)
		,offset(0)
		,Location(-1)
	{

	}
};

class Geometry: public BaseObject
{
public:
	Geometry();
	virtual ~Geometry();

	void create(const std::vector<const VertexAttribute*>& attributes, int vertexCount, int indexCount, bool useVBO=true);

	void clear();

	//@data: data to append
	//@dataSize: data size in byte
	void appendVertexData(float* data, int dataSize);

	int getVertexFSize() { return m_vertexFSize; }

	void render(const ShaderProgramPtr& shader);

private:
	void getAttributeLocations(const ShaderProgramPtr& shader);
	

private:
	int m_attributeCount;
	VertexAttribute* m_attributes;
	int m_vertexFSize; //vertex size in float

	int m_vertexCount;
	GLfloat* m_vertexData;
	GLuint m_vbo;

	int m_indexCount;
	GLushort* m_indices;

	GLfloat* m_vertexAppendPointer;
};



NS_ESLIB_END

#endif //ESL_GEOMETRY_H