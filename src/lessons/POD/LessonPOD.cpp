#include "LessonPOD.h"
#include "pod/PVRTModelPOD.h"

static GLuint uMVPMatrixLoc;
static GLuint uTextureLoc;
static GLuint aPositionLoc;
static GLuint aTexCoordLoc;

struct SMeshSetVBO
{
	GLuint vboVertices;
	GLuint vboIndices;
};

static SMeshSetVBO* s_pMeshVBOs;

static GLuint cub_texture;

static CPVRTModelPOD s_PODScene;

static bool loadVBOs(const CPVRTModelPOD& PodScene)
{	
	int meshNum = PodScene.nNumMesh;
	if(meshNum<=0)
	{
		printf("POD error: No mesh found in pod.\n");
		return false;
	}

	if(!PodScene.pMesh[0].pInterleaved)
	{
		printf("POD error: Requires the pod data to be interleaved. Please re-export with the interleaved option enabled.");
		return false;
	}

	s_pMeshVBOs = new SMeshSetVBO[meshNum];

	for(int i=0; i<meshNum; i++)
	{
		//load vertex data into buffer object
		SPODMesh& mesh = PodScene.pMesh[i];
		unsigned int vertex_data_size = mesh.nNumVertex * mesh.sVertex.nStride;
		s_pMeshVBOs[i].vboVertices = esCreateBufferObject(GL_ARRAY_BUFFER, vertex_data_size, mesh.pInterleaved);

		//load index data into buffer object if available
		s_pMeshVBOs[i].vboIndices = 0;
		if(mesh.sFaces.pData)
		{
			unsigned int index_data_size = PVRTModelPODCountIndices(mesh)*sizeof(GLushort);
			s_pMeshVBOs[i].vboIndices = esCreateBufferObject(GL_ELEMENT_ARRAY_BUFFER, index_data_size, mesh.sFaces.pData);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}

int LessonPOD::onInit(ESContext* esContext)
{
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

	if(PVR_SUCCESS!=s_PODScene.ReadFromFile("media/pod_test/Scene.pod"))
	{
		return FALSE;
	}
	//create buffer objects
	

	if(!loadVBOs(s_PODScene))
		return FALSE;

	//create shaders

	char* vsSrc = 0;
	esLoadFile("media/texture.vs", &vsSrc);

	char* fsSrc = 0;
	esLoadFile("media/texture.fs", &fsSrc);

	GLuint vs, fs;
	vs = esLoadShader(GL_VERTEX_SHADER, vsSrc);
	fs = esLoadShader(GL_FRAGMENT_SHADER, fsSrc);

	GLuint program;
	program = esCreateProgram(vs, fs);

	UserData *userData = (UserData*)esContext->userData;
	userData->programObject = program;
		

	uMVPMatrixLoc = glGetUniformLocation(program, "u_mvpMatrix");
	uTextureLoc = glGetUniformLocation(program, "u_map");

	aPositionLoc = glGetAttribLocation(program, "a_position");
	aTexCoordLoc = glGetAttribLocation(program, "a_texCoord");

	glEnableVertexAttribArray(aPositionLoc);
	glEnableVertexAttribArray(aTexCoordLoc);

	cub_texture = esCreateTextureFromTGA("media/pod_test/tex_base.tga");

	glEnable(GL_DEPTH_TEST);	

	return TRUE;
}

static void drawMesh(const CPVRTModelPOD& PODScene, SMeshSetVBO* MeshVBOs, int NodeIndex)
{
	int meshIndex = PODScene.pNode[NodeIndex].nIdx;
	SPODMesh* pMesh = &PODScene.pMesh[meshIndex];

	glBindBuffer(GL_ARRAY_BUFFER, MeshVBOs[meshIndex].vboVertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MeshVBOs[meshIndex].vboIndices);

	int stride = 5*sizeof(GLfloat);
	glVertexAttribPointer(aPositionLoc, 3, GL_FLOAT, GL_FALSE, pMesh->sVertex.nStride, pMesh->sVertex.pData);
	glVertexAttribPointer(aTexCoordLoc, 2, GL_FLOAT, GL_FALSE, pMesh->psUVW[0].nStride, pMesh->psUVW[0].pData);

	//The gemotry can be exported in 4 ways:
	// - Indexed Triangle List
	// - Non-Indexed Triangle List
	// - Indexed Triangle Strips
	// - Non-Indexed Triangle Strips
	if(pMesh->nNumStrips==0)
	{
		if(MeshVBOs[meshIndex].vboIndices)
		{
			//Indexed triangle list
			glDrawElements(GL_TRIANGLES, pMesh->nNumFaces*3, GL_UNSIGNED_SHORT, 0);
		}
		else
		{
			//Non-Indexed triangle list
			glDrawArrays(GL_TRIANGLES, 0, pMesh->nNumFaces*3);
		}
	}
	else
	{
		int offset = 0;

		for(int i=0; i<(int)pMesh->nNumStrips; ++i)
		{
			if(MeshVBOs[meshIndex].vboIndices)
			{
				//Indexed triangle strips
				glDrawElements(GL_TRIANGLE_STRIP, pMesh->pnStripLength[i]+2, GL_UNSIGNED_SHORT, &((GLshort*)0)[offset]);
			}
			else
			{
				//Non-Indexed triangle strips
				glDrawArrays(GL_TRIANGLE_STRIP, offset, pMesh->pnStripLength[i]+2);
			}

			offset+= pMesh->pnStripLength[i]+2;
		}
	}
	
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}

void LessonPOD::draw(ESContext* esContext)
{
	glViewport(0, 0, esContext->width, esContext->height);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//----------- compute mvpMatrix ---------------------
	static float rotation = 0.0f;
	rotation += 0.05f;

	ESMatrix matRotY, matRotX, matModelView, matProjection;
	ESMatrix matModelViewProjection;

	esMatrixRotateX(matRotX, -rotation * 0.25f);
	esMatrixRotateY(matRotY, rotation);

	esMatrixMultiply(matRotY, matRotX, matModelView);

	esMatrixSetTranslate(matModelView, 0, 0, -500);

	esMatrixPerspective(matProjection, 45.0f, 0.1f, 1000.0f, (float)esContext->width/esContext->height);

	esMatrixMultiply(matProjection, matModelView, matModelViewProjection);

	//-------------------------------------------------

	UserData *userData = (UserData*)esContext->userData;

	glUseProgram(userData->programObject);

	//set the uniform to MVP matrix
	glUniformMatrix4fv(uMVPMatrixLoc, 1, GL_FALSE, matModelViewProjection);

	//bind the texture to an texture unit
	glActiveTexture(GL_TEXTURE1);//just for illustration
	glBindTexture(GL_TEXTURE_2D, cub_texture);

	//set the uniform to the desired texture unit
	glUniform1i(uTextureLoc, 1);

	/*
		A scene is composed of nodes. There are 3 types of nodes:
		- MeshNodes :
			references a mesh in the pMesh[].
			These nodes are at the beginning of the pNode[] array.
			And there are nNumMeshNode number of them.
			This way the .pod format can instantiate several times the same mesh
			with different attributes.
		- lights
		- cameras
		To draw a scene, you must go through all the MeshNodes and draw the referenced meshes.
	*/
	for(unsigned int i=0; i<s_PODScene.nNumMeshNode; ++i)
	{
		SPODNode& node = s_PODScene.pNode[i];

		//set node matrix
		PVRTMat4 mWorld;
		mWorld = s_PODScene.GetWorldMatrix(node);

		//TODO: set texture for node

		//draw node
		drawMesh(s_PODScene, s_pMeshVBOs, i);
	}

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void LessonPOD::update(ESContext* esContext, float dt)
{

}