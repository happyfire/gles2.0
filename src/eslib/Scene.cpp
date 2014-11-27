#include "Scene.h"
#include "components/Camera.h"
#include "components/Transform.h"

NS_ESLIB_BEGIN

Scene::Scene()
{
    m_root = new GameObject();
}

Scene::~Scene()
{
    
}

const GameObjectPtr& Scene::getRoot()
{
    return m_root;
}

GameObjectPtr Scene::createCamera()
{
    GameObjectPtr camera = new GameObject();
    camera->addComponent(new Camera());
    return camera;
}

void Scene::setCurrentCamera(const GameObjectPtr& cameraObject)
{
    m_currentCamera = cameraObject;
}

GameObjectPtr& Scene::getCurrentCamera()
{
    return m_currentCamera;
}

void Scene::render()
{
    if (!m_currentCamera.isValid()) {
        return;
    }
    
    Camera* cameraComp = m_currentCamera->getCamera();
    const Matrix4& matProjection = cameraComp->getProjectionMatrix();
    const Matrix4& matView = cameraComp->getViewMatrix();
    Matrix4 matViewProjection;
    multiplyMatrix(matProjection, matView, matViewProjection);
    
    GameObjectList& children = m_root->getChildren();
    GameObjectIter iter = children.begin();
    
    for (GameObjectIter iterEnd=children.end(); iter!=iterEnd; ++iter)
    {
        GameObjectPtr& obj = *iter;
        
        const Matrix4& objMat = obj->getTransform()->getAbsoluteTransform();
        Matrix4 mvp;
        multiplyMatrix(matViewProjection, objMat, mvp);
        obj->getTransform()->setMVPMatrix(mvp);
        
        obj->render();
    }
}

void Scene::update(float dt)
{
    //m_root->getTransform()->updateAbsoluteTransform(true);
    
}

NS_ESLIB_END

