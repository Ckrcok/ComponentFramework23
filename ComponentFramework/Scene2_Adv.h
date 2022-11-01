#ifndef SCENE2_ADV_H
#define SCENE2_ADV_H
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
class Trackball;
class Scene2_Adv : public Scene {
private:
	GameObject *skull, *lEye, *rEye;
	Vec3 lightSource;
	Mesh *skullMesh, *eyeMesh;
	Shader *shaderPtr;
	Texture *skullTexture, *eyeTexture;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Trackball *trackball;
	Vec3 cameraPos;
	bool buildSkull();
	bool buildEyes();
public:
	explicit Scene2_Adv();
	virtual ~Scene2_Adv();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE2_ADV_H