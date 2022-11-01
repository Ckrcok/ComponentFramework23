#ifndef SCENE4_H
#define SCENE4_H
#include "Scene.h"


/// Forward declarations 
union SDL_Event;


class Scene4 : public Scene {
private:

	class Camera* camera;
	class GameObject *gameObject;
	class Mesh *mesh;
	class Shader *shader;

public:
	explicit Scene4();
	virtual ~Scene4();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE4_H