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
#include "Scene.h"

#include "LessonCube.h"

USING_NS_ESLIB

enum{
    Tag_Cube1 = 1,
    Tag_Cube2,
};

static ScenePtr g_scene;

GameObjectPtr createCube()
{
    GameObjectPtr cubeObj;
    
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
    
    //create mesh
    MeshPtr mesh = new Mesh();
    
    //create geometry
    GeometryPtr geometry = mesh->createEmpty(MVF_POS_3F|MVF_TCOORD_2F, 20, 36, true);
    geometry->appendVertexData(0, cubeStructure, sizeof(cubeStructure));
    geometry->appendIndexData(cubeIndices, sizeof(cubeIndices));
    
    //create material
    MaterialPtr material = new Material();
    material->setShaderProgramFromFile("media/texture.vs","media/texture.fs").setTextureProperty("u_map","media/cube.tga").setTextureProperty("u_map2","media/cube2.tga");
    material->updateShaderProperites();
    
    mesh->setMaterial(material);
    
    //mesh renderer
    MeshRenderer* mesh_renderer = new MeshRenderer();
    mesh_renderer->setMesh(mesh);
    
    //game object with mesh renderer
    cubeObj = new GameObject();
    cubeObj->addComponent(mesh_renderer);
    
    return cubeObj;
}

int LessonCube::onInit()
{
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
    
    g_scene = new Scene();

    //cube1
    GameObjectPtr cube1 = createCube();
    cube1->setTag(Tag_Cube1);
    
    cube1->getTransform()->setPosition(0, 0, 0);
    
    g_scene->getRoot()->addChild(cube1);
    
    //cube2
    GameObjectPtr cube2 = createCube();
    cube2->setTag(Tag_Cube2);
    
    cube2->getTransform()->setPosition(2, 0, 0);
    
    g_scene->getRoot()->addChild(cube2);
    
    //camera
    int screenWidth = Application::GetScreenWidth();
    int screenHeight = Application::GetScreenHeight();
    
    GameObjectPtr camera = g_scene->createCamera();
    camera->getCamera()->setPerspectiveProjection(60.0f, 0.1f, 100.0f, (float)screenWidth/screenHeight);
    camera->getTransform()->setPosition(0, 0, 10);
    camera->getCamera()->setTarget(Vector3(0,0,0));
    
    g_scene->getRoot()->addChild(camera);
    g_scene->setCurrentCamera(camera);
    
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

    
    g_scene->render();
}

void LessonCube::update(float dt)
{
    g_scene->update(dt);
    
    static float rotation = 0.0f;
    rotation += 0.1f*dt*1000;
    
    //----------- compute mvpMatrix ---------------------
    
    GameObject* cube1 = g_scene->getRoot()->getChildByTag(Tag_Cube1);
    Quaternion qx, qy;
    qx.fromAxisAngle(Vector3(1,0,0), -rotation * 0.25f);
    qy.fromAxisAngle(Vector3(0,1,0), rotation);
    cube1->getTransform()->setRotation(qy*qx);
    
    GameObject* camera = g_scene->getCurrentCamera();
    
    camera->getTransform()->setPosition(10*sin(degreeToRadian(rotation*2)), 0, 10*cos(degreeToRadian(rotation*2)));
}

