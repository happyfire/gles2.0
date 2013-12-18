#include "eslib/Application.h"
#include "eslib/Shader.h"
#include "eslib/ShaderProgram.h"
#include "eslib/Geometry.h"
#include "eslib/Material.h"
#include "eslib/Mesh.h"
#include "esUtil/esUtil.h"

#include "LessonCube.h"

USING_NS_ESLIB


static ESMatrix g_matProjection, g_matModelViewProjection;

static MeshPtr g_mesh;

int LessonCube::onInit()
{
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

	//create buffer objects
	GLfloat cubeStructure[]=
	{
		0.50, -0.50, -0.50, -0.00, 0.00,
		0.50, -0.50, 0.50, 0.33, 0.00,
		-0.50, -0.50, 0.50, 0.33, 0.33,
		-0.50, -0.50, -0.50, -0.00, 0.33,
		0.50, 0.50, -0.50, 0.67, 0.33,
		0.50, -0.50, -0.50, 0.33, 0.33,
		-0.50, -0.50, -0.50, 0.33, 0.00,
		-0.50, 0.50, -0.50, 0.67, 0.00,
		0.50, 0.50, 0.50, 0.67, 0.67,
		0.50, -0.50, 0.50, 0.33, 0.67,
		-0.50, 0.50, 0.50, 0.67, 1.00,
		-0.50, -0.50, 0.50, 0.33, 1.00,
		-0.50, 0.50, -0.50, 0.33, 1.00,
		-0.50, -0.50, -0.50, -0.00, 1.00,
		-0.50, -0.50, 0.50, -0.00, 0.67,
		-0.50, 0.50, 0.50, 0.33, 0.67,
		-0.50, 0.50, 0.50, -0.00, 0.67,
		0.50, 0.50, 0.50, -0.00, 0.33,
		0.50, 0.50, -0.50, 0.33, 0.33,
		-0.50, 0.50, -0.50, 0.33, 0.67,
	};

	GLushort cubeIndices[]=
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		8, 9, 5,
		5, 4, 8,
		10, 11, 9,
		9, 8, 10,
		12, 13, 14,
		14, 15, 12,
		16, 17, 18,
		18, 19, 16,
	};

	g_mesh = new Mesh();

	GeometryPtr geometry = g_mesh->createEmpty(MVF_POS_3F|MVF_TCOORD_2F, 20, 36, true);
	geometry->appendVertexData(0, cubeStructure, sizeof(cubeStructure));
	geometry->appendIndexData(cubeIndices, sizeof(cubeIndices));


	//create material
	MaterialPtr material = new Material();
	material->setShaderProgramFromFile("media/texture.vs","media/texture.fs").setTextureProperty("u_map","media/cube.tga").setTextureProperty("u_map2","media/cube2.tga");
	material->updateShaderProperites();

	g_mesh->setMaterial(material);

	glEnable(GL_DEPTH_TEST);
    
    int screenWidth = Application::GetScreenWidth();
	int screenHeight = Application::GetScreenHeight();
    
    esMatrixPerspective(g_matProjection, 45.0f, 0.1f, 100.0f, (float)screenWidth/screenHeight);

	return 1;
}



void LessonCube::draw()
{
	int screenWidth = Application::GetScreenWidth();
	int screenHeight = Application::GetScreenHeight();

	glViewport(0, 0, screenWidth, screenHeight);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	

	//-------------------------------------------------

	g_mesh->setTransform(g_matModelViewProjection);
	
	g_mesh->render();

	
}

void LessonCube::update(float dt)
{
    static float rotation = 0.0f;
    rotation += 0.1f*dt*1000;
    
    //----------- compute mvpMatrix ---------------------
	
    
	ESMatrix matRotY, matRotX, matModelView;
    
	esMatrixRotateX(matRotX, -rotation * 0.25f);
	esMatrixRotateY(matRotY, rotation);
    
	esMatrixMultiply(matRotY, matRotX, matModelView);
    
	esMatrixSetTranslate(matModelView, 0, 0, -3);
    
	esMatrixMultiply(g_matProjection, matModelView, g_matModelViewProjection);
}

