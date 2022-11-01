#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <glew.h>
#include "Matrix.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Object.h"
#include "PhysicsObject.h"

using namespace MATH;


class GameObject: public PhysicsObject, public Object {	

private:
	Matrix4 modelMatrix;
	Mesh *mesh;
	Shader *shader;
	Texture *texture;
	GameObject *parent;
public:
	GameObject(Mesh *mesh_, Shader *shader_, Texture *texture_);
	GameObject(GameObject *parent_, Mesh *mesh_, Shader *shader_, Texture *texture_);

	~GameObject();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event &event);


	inline Shader* getShader() const { return shader; }
	inline void setModelMatrix(const Matrix4 &modelMatrix_) { modelMatrix = modelMatrix_; }
	inline const Matrix4& getModelMatrix() { return modelMatrix; }
};

#endif /// GAMEOBJECT_H

