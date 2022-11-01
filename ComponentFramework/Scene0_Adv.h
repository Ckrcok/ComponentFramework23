#ifndef SCENE0_ADV_H
#define SCENE0_ADV_H
#include "Scene.h"
#include <Vector.h>
#include <Matrix.h>
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class GameObject;
class Mesh;
class Shader;
class Texture;

class Scene0_Adv : public Scene {
private:
	GameObject* gameObject;
	Vec3 lightSource;
	Mesh* meshPtr;
	Shader* shaderPtr;
	Texture* texturePtr;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
public:
	explicit Scene0_Adv();
	virtual ~Scene0_Adv();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE0_ADV_H