#include "eslib/Application.h"
#include "eslib/Shader.h"
#include "eslib/ShaderProgram.h"
#include "eslib/Geometry.h"
#include "eslib/Material.h"
#include "eslib/Mesh.h"
#include "esUtil/esUtil.h"

#include "eslib/base/GameObject.h"
#include "eslib/base/Component.h"
#include "eslib/components/MeshRenderer.h"

#include "LessonMD2.h"
#include "MD2MeshLoader.h"

USING_NS_ESLIB


static ESMatrix g_matProjection, g_matModelViewProjection;

//static MeshPtr g_mesh;

static GameObjectPtr g_obj;

int LessonMD2::onInit()
{
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
    
    MD2MeshLoader md2Loader;
	MeshPtr mesh = md2Loader.load("media/tris.MD2","media/tris.tga");
    
    g_obj = new GameObject();
    MeshRenderer* mesh_renderer = new MeshRenderer();
    mesh_renderer->setMesh(mesh);
    g_obj->setComponent(mesh_renderer);

	glEnable(GL_DEPTH_TEST);
    
    int screenWidth = Application::GetScreenWidth();
	int screenHeight = Application::GetScreenHeight();
    
    esMatrixPerspective(g_matProjection, 45.0f, 0.1f, 1000.0f, (float)screenWidth/screenHeight);

	return 1;
}



void LessonMD2::draw()
{
	int screenWidth = Application::GetScreenWidth();
	int screenHeight = Application::GetScreenHeight();

	glViewport(0, 0, screenWidth, screenHeight);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	

	//-------------------------------------------------
    
    MeshRenderer* mesh_renderer = static_cast<MeshRenderer*>(g_obj->getComponent("MeshRenderer"));
    mesh_renderer->getMesh()->setTransform(g_matModelViewProjection); //TODO: move transform to Transform component
    mesh_renderer->render(); //TODO: add a IRenderer componenet interface
}

void LessonMD2::update(float dt)
{
    static float rotation = 0.0f;
    rotation += 0.1f*dt*1000;
    
    //----------- compute mvpMatrix ---------------------
	
    
	ESMatrix matRotY, matRotX, matModelView;
    
	esMatrixRotateX(matRotX, 3.1415926/2);
	esMatrixRotateY(matRotY, rotation);
    
	esMatrixMultiply(matRotY, matRotX, matModelView);
    
	esMatrixSetTranslate(matModelView, 0, 0, -200);
    
	esMatrixMultiply(g_matProjection, matModelView, g_matModelViewProjection);
}

