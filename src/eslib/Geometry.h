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
	int VertexStreamID; //default is 0, the max vertex stream id is the "attribute count-1"
	int offset; //offset in its data stream, in float
	int Location;
	std::string Name; //Name in shader

	VertexAttribute()
		:ElementCount(0)
		,VertexStreamID(0)
		,offset(0)
		,Location(-1)
	{

	}
};

struct VertexDataStream
{
	int VertexFSize; //size in float of vertex attributes of a single vertex in this stream
	GLfloat* VertexData;
	GLuint vbo;
	GLfloat* m_vertexAppendPointer;

	VertexDataStream()
		:VertexFSize(0)
		,VertexData(null)
		,vbo(0)
		,m_vertexAppendPointer(null)
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

	//@streamID: the id of vertex stream
	//@data: data to append
	//@dataSize: data size in byte
	void appendVertexData(int streamID, float* data, int dataSize);

	void appendIndexData(GLushort* data, int dataSize);

	void render(const ShaderProgramPtr& shader);

private:
	void getAttributeLocations(const ShaderProgramPtr& shader);
	

private:
	int m_attributeCount;
	VertexAttribute* m_attributes;
	//int m_vertexFSize; //vertex size in float

	int m_vertexCount;

	int m_vertexStreamCount;
	VertexDataStream* m_vertexStreams;

	//GLfloat* m_vertexData;
	//GLuint m_vbo;

	int m_indexCount;
	GLushort* m_indices;
	GLuint m_vboIndex;

	//GLfloat* m_vertexAppendPointer;
	GLushort* m_indexAppendPointer;
};



NS_ESLIB_END

#endif //ESL_GEOMETRY_H