#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "../../Core/Component.h"

class GameObject
{
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();
	
	void Render(Camera* camera_);
	void Update(const float deltaTime_);


	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	float GetAngle() const;
	glm::vec3 GetScale() const;
	BoundingBox GetBoundingBox();
	std::string GetTag() const; 
	bool GetHit() const; 

	void SetPosition(glm::vec3 pos_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);

	template<typename TComponent>
	void AddComponent() {
		TComponent* newComponent = new TComponent();

		if (dynamic_cast<Component*>(newComponent) == nullptr) {
			Debugger::FatalError("New object is NOT a child of the Component base class!", "GameObject.cpp", __LINE__);
			delete newComponent; //deleting the component  
			newComponent = nullptr;

			return; //Stop the function 
		}

		if (GetComponent<TComponent>() != nullptr) {
			Debugger::FatalError("Game Object has too many of the same component!", "GameObject.cpp", __LINE__);
			delete newComponent; //deleting the component  
			newComponent = nullptr;

			return; //Stop the function
		}

		ComponentObjects.push_back(newComponent);
		newComponent->OnCreate(this);
	}

	template<typename TComponent>
	TComponent* GetComponent() {
		for (auto componentObject : ComponentObjects) {
			if (dynamic_cast<TComponent*>(componentObject)) {
				return dynamic_cast<TComponent*>(componentObject);
			}
		}

		return nullptr;
	}

	template<typename TComponent>
	void RemoveComponent() {
		for (int i = 0; i < ComponentObjects.size(); i++) {
			if (dynamic_cast<TComponent*>(ComponentObjects[i])) {
				delete ComponentObjects[i];
				ComponentObjects[i] = nullptr;
				ComponentObjects.erase(ComponentObjects.begin() + i);
					break;
			}
		}
	}

private:
	Model* model;
	glm::vec3 position;
	glm::vec3 rotation;
	float angle;
	glm::vec3 scale;

	int modelInstance; 
	BoundingBox box; 

	std::string tag; 
	bool hit; 

	std::vector<Component*> ComponentObjects; 
};

#endif

