#include "Geometry.h"
#include "ShaderProgram.h"

NS_ESLIB_BEGIN


Geometry::Geometry(int primitiveType)
	:m_primitiveType(primitiveType)
    ,m_attributeCount(0)
	,m_attributes(null)
	,m_vertexCount(0)
	,m_vertexStreamCount(0)
	,m_vertexStreams(null)
	,m_indexCount(0)
	,m_indices(null)
	,m_vboIndex(0)
	,m_indexAppendPointer(null)
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
	
	m_vertexCount = 0;
	
	for(int i=0; i<m_vertexStreamCount; i++)
	{
		VertexDataStream& vds = m_vertexStreams[i];

		ESL_SAFE_DEL_ARRAY(vds.VertexData);
		if(vds.vbo>0)
		{
			glDeleteBuffers(1, &vds.vbo);
		}

		vds.VertexFSize = 0;
		vds.m_vertexAppendPointer = null;
	}
	
	m_indexCount = 0;
	ESL_SAFE_DEL_ARRAY(m_indices);
    if(m_vboIndex>0)
    {
        glDeleteBuffers(1, &m_vboIndex);
    }

	m_indexAppendPointer = null;
}

void Geometry::create(const std::vector<const VertexAttribute*>& attributes, int vertexCount, int indexCount, bool useVBO)
{
	clear();

	//attributes
	m_attributeCount = attributes.size();

	ESL_ASSERT(m_attributeCount>0);

	//at first, find out vertex data stream count, and create vertex stream array
	m_vertexStreamCount = 1;
	for(int i=0; i<m_attributeCount; i++)
	{
		if(attributes[i]->VertexStreamID >= m_vertexStreamCount)
		{
			m_vertexStreamCount++;
		}
	}
	m_vertexStreams = new VertexDataStream[m_vertexStreamCount];

	//create attributes
	m_attributes = new VertexAttribute[m_attributeCount];

	for(int i=0; i<m_attributeCount; i++)
	{
		ESL_ASSERT(attributes[i]->ElementCount>=1 && attributes[i]->ElementCount<=4);

		m_attributes[i].ElementCount = attributes[i]->ElementCount;
		m_attributes[i].Name = attributes[i]->Name;
        m_attributes[i].Type = attributes[i]->Type;

		int vsID = attributes[i]->VertexStreamID;

		m_attributes[i].VertexStreamID = vsID;
		
		m_attributes[i].offset = m_vertexStreams[vsID].VertexFSize;
		m_vertexStreams[vsID].VertexFSize += m_attributes[i].ElementCount;
	}

	//vertex stream data
	ESL_ASSERT(vertexCount>0);
	m_vertexCount = vertexCount;

	for(int i=0; i<m_vertexStreamCount; i++)
	{
		VertexDataStream& vds = m_vertexStreams[i];

		vds.VertexData = new GLfloat[vds.VertexFSize*m_vertexCount];

		if(useVBO)
		{
			glGenBuffers(1, &vds.vbo);
		}
	}	

	//index
	ESL_ASSERT(indexCount>=0);
	m_indexCount = indexCount;
	if(m_indexCount>0)
	{
		m_indices = new GLushort[m_indexCount];

		if(useVBO)
		{
			glGenBuffers(1, &m_vboIndex);
		}
	}
}

void Geometry::appendVertexData(int streamID, float* data, int dataSize)
{
	ESL_ASSERT(streamID>=0 && streamID<m_vertexStreamCount);

	VertexDataStream& vds = m_vertexStreams[streamID];

	ESL_ASSERT(vds.VertexData!=null);

	if(vds.m_vertexAppendPointer==null)
	{
		vds.m_vertexAppendPointer = vds.VertexData;
	}

	memcpy(vds.m_vertexAppendPointer, data, dataSize);

	vds.m_vertexAppendPointer += dataSize/sizeof(GLfloat);

	if(vds.m_vertexAppendPointer==vds.VertexData+vds.VertexFSize * m_vertexCount)
	{
        computeAABB(streamID, vds);
        
        if (vds.vbo>0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vds.vbo);
            glBufferData(GL_ARRAY_BUFFER, vds.VertexFSize * m_vertexCount * sizeof(GLfloat), vds.VertexData, GL_STATIC_DRAW);
            delete[] vds.VertexData;
            vds.VertexData = null;
            vds.m_vertexAppendPointer = null;
        }
	}
}

void Geometry::appendIndexData(GLushort* data, int dataSize)
{
	ESL_ASSERT(m_indices!=null);

	if(m_indexAppendPointer==null)
	{
		m_indexAppendPointer = m_indices;
	}

	memcpy(m_indexAppendPointer, data, dataSize);

	m_indexAppendPointer += dataSize/sizeof(GLushort);

	if(m_vboIndex>0 && m_indexAppendPointer==m_indices+m_indexCount)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount*sizeof(GLushort), m_indices, GL_STATIC_DRAW);
		delete[] m_indices;
		m_indices = null;
		m_indexAppendPointer = null;
	}
}

void Geometry::computeAABB(int streamID, VertexDataStream &vds)
{
    Vector3 point;
    
    for(int i=0; i<m_attributeCount; i++)
    {
        VertexAttribute& attr = m_attributes[i];
        
        if(attr.Type==Type_Position && attr.VertexStreamID==streamID)
        {
            GLfloat* posData = vds.VertexData + attr.offset;
            point.set(*posData, *(posData+1), *(posData+2));
            m_aabb.reset(point);
            
            for (int vi=1; vi<m_vertexCount; vi++) {
                posData+=vds.VertexFSize;
                
                point.set(*posData, *(posData+1), *(posData+2));
                m_aabb.addPoint(point);
            }
            
            break;
        }
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
	if(m_vboIndex>0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
	}
	else
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	

	getAttributeLocations(shader);

	for(int i=0; i<m_attributeCount; i++)
	{
		if(m_attributes[i].Location>=0)
		{
			VertexDataStream& vds = m_vertexStreams[m_attributes[i].VertexStreamID];

			if(vds.vbo>0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, vds.vbo);
			}
			else
			{
				//If used vbo before without VBO, should bind vbo to 0 to clear it, or else will crash ( no buffer data found)
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			glEnableVertexAttribArray(m_attributes[i].Location);

			if(vds.vbo>0)
			{
				glVertexAttribPointer(m_attributes[i].Location, m_attributes[i].ElementCount, 
					GL_FLOAT, GL_FALSE, vds.VertexFSize*sizeof(GLfloat), (const void*)(m_attributes[i].offset*sizeof(GLfloat)));
			}
			else
			{
				glVertexAttribPointer(m_attributes[i].Location, m_attributes[i].ElementCount, 
					GL_FLOAT, GL_FALSE, vds.VertexFSize*sizeof(GLfloat), vds.VertexData+m_attributes[i].offset);
			}
		}
	}

	if(m_indexCount>0)
	{
		if(m_vboIndex>0)
		{
			glDrawElements(m_primitiveType, m_indexCount, GL_UNSIGNED_SHORT, (void*)0);
		}
		else
		{
			glDrawElements(m_primitiveType, m_indexCount, GL_UNSIGNED_SHORT, m_indices);
		}
	}
	else
	{
		glDrawArrays(m_primitiveType, 0, m_vertexCount);
	}
}

const AABBox& Geometry::getAABB() const
{
    return m_aabb;
}

NS_ESLIB_END
