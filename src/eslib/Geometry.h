#ifndef ESL_GEOMETRY_H
#define ESL_GEOMETRY_H

#include "BaseObject.h"
#include "sharedPtr.h"
#include "glcommon.h"
#include <vector>
#include "eslib/scene/AABBox.h"


NS_ESLIB_BEGIN

ESL_FORWARD_PTR(ShaderProgram)
ESL_FORWARD_PTR(Geometry)

//Shader class, vertex or fragment shader

enum AttributeType
{
    Type_Custom,
    Type_Position,
    Type_Normal,
    Type_UV,
};

struct VertexAttribute
{
	int ElementCount;
	int VertexStreamID; //default is 0, the max vertex stream id is the "attribute count-1"
	int offset; //offset in its data stream, in float
	int Location;
	std::string Name; //Name in shader
    AttributeType Type;

	VertexAttribute()
		:ElementCount(0)
		,VertexStreamID(0)
		,offset(0)
		,Location(-1)
        ,Type(Type_Custom)
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
	Geometry(int primitiveType=GL_TRIANGLES);
	virtual ~Geometry();
    
	void create(const std::vector<const VertexAttribute*>& attributes, int vertexCount, int indexCount, bool useVBO=true);

	void clear();
    
    void resetAppendVertexData(int streamID);

	//@streamID: the id of vertex stream
	//@data: data to append
	//@dataSize: data size in byte
	void appendVertexData(int streamID, float* data, int dataSize);

	void appendIndexData(GLushort* data, int dataSize);

	void render(const ShaderProgramPtr& shader);
    
    const AABBox& getAABB() const;

private:
	void getAttributeLocations(const ShaderProgramPtr& shader);
	
    void computeAABB(int streamID, VertexDataStream &vds);
    
private:
    int m_primitiveType;
    
	int m_attributeCount;
	VertexAttribute* m_attributes;

	int m_vertexCount;

	int m_vertexStreamCount;
	VertexDataStream* m_vertexStreams;

	int m_indexCount;
	GLushort* m_indices;
	GLuint m_vboIndex;

	GLushort* m_indexAppendPointer;
    
    AABBox m_aabb;
};



NS_ESLIB_END

#endif //ESL_GEOMETRY_H