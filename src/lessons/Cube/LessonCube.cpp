#include "eslib/Application.h"
#include "eslib/Shader.h"
#include "eslib/ShaderProgram.h"
#include "eslib/Geometry.h"
#include "eslib/Material.h"
#include "eslib/Mesh.h"
#include "esUtil/esUtil.h"
#include "eslib/math/Matrix4.h"
#include "eslib/base/GameObject.h"
#include "eslib/components/MeshRenderer.h"
#include "eslib/components/Transform.h"
#include "eslib/components/Camera.h"

#include "LessonCube.h"

USING_NS_ESLIB


static ESMatrix g_matModelView;

static GameObjectPtr g_obj;
static GameObjectPtr g_camera;

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

	MeshPtr mesh = new Mesh();

	GeometryPtr geometry = mesh->createEmpty(MVF_POS_3F|MVF_TCOORD_2F, 20, 36, true);
	geometry->appendVertexData(0, cubeStructure, sizeof(cubeStructure));
	geometry->appendIndexData(cubeIndices, sizeof(cubeIndices));


	//create material
	MaterialPtr material = new Material();
	material->setShaderProgramFromFile("media/texture.vs","media/texture.fs").setTextureProperty("u_map","media/cube.tga").setTextureProperty("u_map2","media/cube2.tga");
	material->updateShaderProperites();

	mesh->setMaterial(material);

	MeshRenderer* mesh_renderer = new MeshRenderer();
	mesh_renderer->setMesh(mesh);

	g_obj = new GameObject();
	g_obj->addComponent(mesh_renderer);
    
    g_obj->getTransform()->setPosition(0, 0, 0);
    
    int screenWidth = Application::GetScreenWidth();
    int screenHeight = Application::GetScreenHeight();
    
    g_camera = new GameObject();
    Camera* cam_comp = new Camera();
    cam_comp->setPerspectiveProjection(45.0f, 0.1f, 100.0f, (float)screenWidth/screenHeight);
    g_camera->addComponent(cam_comp);
    
    g_camera->getTransform()->setPosition(0, 0, 10);
    cam_comp->setTarget(Vector3(0,0,-1));

	glEnable(GL_DEPTH_TEST);

	return 1;
}



void LessonCube::draw()
{
	int screenWidth = Application::GetScreenWidth();
	int screenHeight = Application::GetScreenHeight();

	glViewport(0, 0, screenWidth, screenHeight);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//-------------------------------------------------

    
	g_obj->render();
}

void LessonCube::update(float dt)
{
    static float rotation = 0.0f;
    rotation += 0.1f*dt*1000;
    
    //----------- compute mvpMatrix ---------------------
    
    Quaternion qx, qy;
    qx.fromAxisAngle(Vector3(1,0,0), -rotation * 0.25f);
    qy.fromAxisAngle(Vector3(0,1,0), rotation);
    g_obj->getTransform()->setRotation(qy*qx);
    
    Camera* cam_comp = static_cast<Camera*>(g_camera->getComponent("Camera"));
    const Matrix4& matProjection = cam_comp->getProjectionMatrix();
    
    const Matrix4& matView = cam_comp->getViewMatrix();
    
    const Matrix4& objMat = g_obj->getTransform()->getAbsoluteTransform();
    
    Matrix4 mv, mvp;
    multiplyMatrix(matView, objMat, mv);
    multiplyMatrix(matProjection, mv, mvp);
    
    g_obj->getTransform()->setMVPMatrix(mvp);
    
	//ESMatrix matRotY, matRotX;
    
	//esMatrixRotateX(matRotX, -rotation * 0.25f);
	//esMatrixRotateY(matRotY, rotation);
    
	//esMatrixMultiply(matRotY, matRotX, g_matModelView);
    
	//esMatrixSetTranslate(g_matModelView, 0, 0, -3);
    
}

