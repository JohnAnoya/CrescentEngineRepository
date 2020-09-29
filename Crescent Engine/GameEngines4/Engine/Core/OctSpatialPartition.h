#ifndef OCTSPATIALPARTITION_H 
#define OCTSPATIALPARTITION_H

#include "../Math/Ray.h"
#include "../Rendering/3D/GameObject.h"

#define CHILDREN_NUMBER 8

enum class OctChildren {
	OCT_TLF, //Top Left Front 
	OCT_BLF, //Bottom Left Front 
	OCT_BRF, //Bottom Right Front 
	OCT_TRF, //Top Right Front 
	
	OCT_TLR, //Top Right Rear 
	OCT_BLR, //Bottom Left Rear 
	OCT_BRR, //Bottom Right Rear 
	OCT_TRR  //Top Right Rear
};

class OctNode {
public: 
	OctNode(glm::vec3 position_, float size_, OctNode* parent_); 
	~OctNode(); 
	void OnDestroy(); 
	void Octify(int depth_);
	OctNode* GetParent(); 
	OctNode* GetChild(OctChildren childPos_);
	void AddCollisionObject(GameObject* obj_); 
	int GetObjectCount() const;
	bool IsLeaf() const;
	BoundingBox* GetBoundingBox() const; 
	int GetChildCount() const; 
private: 
	friend class OctSpatialPartition; 
	BoundingBox* octBounds; 
	OctNode* parent; 
	OctNode* children[CHILDREN_NUMBER]; 
	std::vector<GameObject*> objectList; 
	float size; 
	static int childNum; 
};

class OctSpatialPartition{
public:
	OctSpatialPartition(float worldSize_); 
	~OctSpatialPartition();
	void OnDestroy();
	void AddObject(GameObject* obj_); 
	GameObject* GetCollision(Ray ray_);
private: 
	OctNode* root; 
	std::vector<OctNode*> rayIntersectionList; 
	void AddObjectToCell(OctNode* cell_, GameObject* obj_);
	void PrepareCollisionQuery(OctNode* cell_, Ray ray_);

};
#endif 