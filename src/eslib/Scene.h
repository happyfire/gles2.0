#ifndef ESL_SCENE_H
#define ESL_SCENE_H

#include "eslib/BaseObject.h"
#include "eslib/sharedPtr.h"
#include "base/GameObject.h"

NS_ESLIB_BEGIN

ESL_FORWARD_PTR(Scene)

class Scene: public BaseObject
{
public:
	Scene();
	virtual ~Scene();
    
    const GameObjectPtr& getRoot();
    
    GameObjectPtr createCamera();
    
    void setCurrentCamera(const GameObjectPtr& cameraObject);
    
    GameObjectPtr& getCurrentCamera();
    
    void render();
    
    void update(float dt);
    
    
protected:
    GameObjectPtr m_root;
    GameObjectPtr m_currentCamera;

	
};



NS_ESLIB_END

#endif //ESL_SCENE_H
