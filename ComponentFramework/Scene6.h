#ifndef SCENE6_H
#define SCENE6_H
#include "Scene.h"
#include <Vector.h>
using namespace MATH;
/// Forward declarations 
union SDL_Event;
class Particles;
class Camera;
class GameObject;
class Mesh;
class Shader;

class Scene6 : public Scene {
private:

	Camera* camera;
	GameObject*gameObject;
	Mesh*mesh;
	Shader* shader;
	float totalTime;
	Vec3 offset;
	GLuint noiseTextureID;
	Particles *particles;

public:
	explicit Scene6();
	virtual ~Scene6();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE6_H