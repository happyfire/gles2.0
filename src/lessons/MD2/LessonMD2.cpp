#include "eslib/Application.h"
#include "eslib/Shader.h"
#include "eslib/ShaderProgram.h"
#include "eslib/Geometry.h"
#include "eslib/Material.h"
#include "eslib/Mesh.h"
#include "esUtil/esUtil.h"

#include "eslib/base/GameObject.h"
#include "eslib/base/Component.h"
#include "eslib/components/Transform.h"
#include "eslib/components/MeshRenderer.h"

#include "eslib/math/Matrix4.h"

#include "LessonMD2.h"
#include "MD2MeshLoader.h"

USING_NS_ESLIB


static Matrix4 g_matProjection;

static GameObjectPtr g_obj, g_obj2;

int LessonMD2::onInit()
{
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
    
    MD2MeshLoader md2Loader;
	MeshPtr mesh = md2Loader.load("media/tris.MD2","media/tris.tga");
    
    g_obj = new GameObject();
    MeshRenderer* mesh_renderer = new MeshRenderer();
    mesh_renderer->setMesh(mesh);
    g_obj->addComponent(mesh_renderer);

	g_obj2 = new GameObject(*g_obj);


	glEnable(GL_DEPTH_TEST);
    
    int screenWidth = Application::GetScreenWidth();
	int screenHeight = Application::GetScreenHeight();

	g_matProjection.makePerspectiveProjectionMatrix(45.0f, 0.1f, 1000.0f, (float)screenWidth/screenHeight);
    
	return 1;
}



void LessonMD2::draw()
{
	int screenWidth = Application::GetScreenWidth();
	int screenHeight = Application::GetScreenHeight();

	glViewport(0, 0, screenWidth, screenHeight);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	

	//-------------------------------------------------
    
	g_obj->render();
	g_obj2->render();
}

void LessonMD2::update(float dt)
{
    static float rotation = 0.0f;
    rotation += 0.1f*dt*1000;
    
    //----------- compute mvpMatrix ---------------------
	
    
	Matrix4 matRotY, matRotX, matModelView, matMVP;
    
    
    //obj1
	g_obj->getTransform()->setRotation(Vector3(1, 0, 0),rotation);
    g_obj->getTransform()->setPosition(0,0,-200);
    matMVP = g_matProjection * g_obj->getTransform()->getAbsoluteTransform();
    g_obj->getTransform()->setMVPMatrix(matMVP);

    //obj2
    matRotX.makeRotateXMatrix(3.1415926/2);
	matRotY.makeRotateYMatrix(rotation);
    matModelView = matRotX * matRotY;
	matModelView.setTranslation(0, 0, -200);
	matModelView.setTranslation(0, 50, -200);
	matMVP = g_matProjection * matModelView;
	
	g_obj2->getTransform()->setMVPMatrix(matMVP);
}

