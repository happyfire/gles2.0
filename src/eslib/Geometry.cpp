#include "Geometry.h"

NS_ESLIB_BEGIN


Geometry::Geometry()
	:m_attributeCount(0)
	,m_attributes(null)
	,m_vertexFSize(0)
	,m_vertexCount(0)
	,m_vertexData(null)
	,m_indexCount(0)
	,m_indices(null)
	,m_vertexAppendPointer(null)
{
}

Geometry::~Geometry()
{
	clear();
}

void Geometry::clear()
{
	m_attributeCount = 0;
	ESL_SAFE_DEL_ARRAY(m_attributes);
	
	m_vertexFSize = 0;
	m_vertexCount = 0;
	ESL_SAFE_DEL_ARRAY(m_vertexData);
	
	m_indexCount = 0;
	ESL_SAFE_DEL_ARRAY(m_indices);

	m_vertexAppendPointer = null;
}

void Geometry::create(const std::vector<int>& attributeElementCounts, int vertexCount, int indexCount)
{
	clear();

	//attributes
	m_attributeCount = attributeElementCounts.size();

	ESL_ASSERT(m_attributeCount>0);

	m_attributes = new VertexAttribute[m_attributeCount];

	m_vertexFSize = 0;

	for(int i=0; i<m_attributeCount; i++)
	{
		ESL_ASSERT(attributeElementCounts[i]>=1 && attributeElementCounts[i]<=4);

		m_attributes[i].ElementCount = attributeElementCounts[i];
		m_attributes[i].offset = m_vertexFSize;
		m_vertexFSize += m_attributes[i].ElementCount;
	}

	//vertex data
	ESL_ASSERT(vertexCount>0);
	m_vertexCount = vertexCount;
	m_vertexData = new GLfloat[m_vertexFSize * m_vertexCount];

	//index
	ESL_ASSERT(indexCount>=0);
	m_indexCount = indexCount;
	if(m_indexCount>0)
	{
		m_indices = new GLushort[m_indexCount];
	}
}

void Geometry::appendVertexData(float* data, int dataSize)
{
	ESL_ASSERT(m_vertexData!=null);

	if(m_vertexAppendPointer==null)
	{
		m_vertexAppendPointer = m_vertexData;
	}

	memcpy(m_vertexAppendPointer, data, dataSize);

	m_vertexAppendPointer += dataSize;
}

void Geometry::setAttribPointer(int location, int attribute)
{
	ESL_ASSERT(attribute>=0 && attribute<m_attributeCount);

	glVertexAttribPointer(location, m_attributes[attribute].ElementCount, GL_FLOAT, GL_FALSE, m_vertexFSize*sizeof(GLfloat), m_vertexData+m_attributes[attribute].offset);
}

NS_ESLIB_END