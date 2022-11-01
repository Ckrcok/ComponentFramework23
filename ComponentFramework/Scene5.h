#ifndef SCENE5_H
#define SCENE5_H
#include "Scene.h"
#include <Vector.h>
#include <Matrix.h>
using namespace MATH;
/// Forward declarations 
union SDL_Event;


class Scene5 : public Scene {
private:

	class Camera* camera;
	class GameObject *gameObject;
	class Mesh *mesh;
	class Shader *shader;
	float totalTime;
	Vec3 offset;
	GLuint noiseTextureID;

public:
	explicit Scene5();
	virtual ~Scene5();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE5_H