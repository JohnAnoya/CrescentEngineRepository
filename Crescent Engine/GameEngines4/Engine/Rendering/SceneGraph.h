#ifndef SCENEGRAPH_H 
#define SCENEGRAPH_H 

#include <memory>
#include <map>
#include <vector>
#include "3D/GameObject.h"
#include "../Math/CollisionHandler.h"

class SceneGraph
{
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph&&) = delete;

	static SceneGraph* GetInstance(); 
	void OnDestroy(); 
	void AddModel(Model* model_); 
	void AddGameObject(GameObject* gameObject_, std::string tag_ = ""); 
	GameObject* GetGameObject(std::string tag_); 
	std::map<std::string, GameObject*> GetSceneGameObjects(); 
	int GetSceneGameObjectsCount(); 

	void Update(const float deltaTime_); 
	void Render(Camera* camera_);
private: 
	SceneGraph(); 
	~SceneGraph(); 

	static std::unique_ptr<SceneGraph> sceneGraphInstance; 
	friend std::default_delete<SceneGraph>; 

	static std::map<GLuint, std::vector<Model*>> sceneModels; 
	static std::map<std::string, GameObject*> sceneGameObjects; 
};

#endif 
