#ifndef SCENE1_ADV_H
#define SCENE1_ADV_H
#include "Scene.h"
#include <Vector.h>
#include <Matrix.h>
#include <vector>

using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Mesh;
class Shader;
class Texture;
class GameObject;



class Scene1_Adv : public Scene {
private:
	Mesh *meshPtr;
	Shader *shaderPtr;
	Texture *texturePtr;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	GameObject *gameObject;

	std::vector <Vec3> lightPos;
	std::vector <Vec4> lightDiffuse;
	std::vector <Vec4> lightSpecular;
	
public:
	explicit Scene1_Adv();
	virtual ~Scene1_Adv();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif /// SCENE1_ADV_H