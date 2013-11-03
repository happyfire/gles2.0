#include "Geometry.h"
#include "ShaderProgram.h"

NS_ESLIB_BEGIN


Geometry::Geometry()
	:m_attributeCount(0)
	,m_attributes(null)
	,m_vertexFSize(0)
	,m_vertexCount(0)
	,m_vertexData(null)
	,m_vbo(0)
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

void Geometry::create(const std::vector<const VertexAttribute*>& attributes, int vertexCount, int indexCount, bool useVBO)
{
	clear();

	//attributes
	m_attributeCount = attributes.size();

	ESL_ASSERT(m_attributeCount>0);

	m_attributes = new VertexAttribute[m_attributeCount];

	m_vertexFSize = 0;

	for(int i=0; i<m_attributeCount; i++)
	{
		ESL_ASSERT(attributes[i]->ElementCount>=1 && attributes[i]->ElementCount<=4);

		m_attributes[i].ElementCount = attributes[i]->ElementCount;
		m_attributes[i].Name = attributes[i]->Name;
		m_attributes[i].offset = m_vertexFSize;
		m_vertexFSize += m_attributes[i].ElementCount;
	}

	//vertex data
	ESL_ASSERT(vertexCount>0);
	m_vertexCount = vertexCount;
	m_vertexData = new GLfloat[m_vertexFSize * m_vertexCount];

	if(useVBO)
	{
		glGenBuffers(1, &m_vbo);
	}

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

	m_vertexAppendPointer += dataSize/sizeof(GLfloat);

	if(m_vbo>0 && m_vertexAppendPointer==m_vertexData+m_vertexFSize * m_vertexCount)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertexFSize * m_vertexCount * sizeof(GLfloat), m_vertexData, GL_STATIC_DRAW);
		delete[] m_vertexData;
		m_vertexData = null;
		m_vertexAppendPointer = null;
	}
}

void Geometry::getAttributeLocations(const ShaderProgramPtr& shader)
{
	for(int i=0; i<m_attributeCount; i++)
	{
		if(m_attributes[i].Location==-1)
		{
			m_attributes[i].Location = glGetAttribLocation(shader->getProgramObject(), m_attributes[i].Name.c_str());
			ESL_ASSERT(m_attributes[i].Location>=0);
		}
	}
}

void Geometry::render(const ShaderProgramPtr& shader)
{
	if(m_vbo>0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	}
	else
	{
		//If used vbo before without VBO, should bind vbo to 0 to clear it, or else will crash ( no buffer data found)
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	

	getAttributeLocations(shader);

	for(int i=0; i<m_attributeCount; i++)
	{
		if(m_attributes[i].Location>=0)
		{
			glEnableVertexAttribArray(m_attributes[i].Location);

			if(m_vbo>0)
			{
				glVertexAttribPointer(m_attributes[i].Location, m_attributes[i].ElementCount, 
					GL_FLOAT, GL_FALSE, m_vertexFSize*sizeof(GLfloat), (const void*)(m_attributes[i].offset*sizeof(GLfloat)));
			}
			else
			{
				glVertexAttribPointer(m_attributes[i].Location, m_attributes[i].ElementCount, 
					GL_FLOAT, GL_FALSE, m_vertexFSize*sizeof(GLfloat), m_vertexData+m_attributes[i].offset);
			}
		}
	}

	if(m_indexCount>0)
	{

	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
	}
}

NS_ESLIB_END