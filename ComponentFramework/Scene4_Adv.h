#ifndef SCENE4_ADV_H
#define SCENE4_ADV_H
#include "Scene.h"


/// Forward declarations 
union SDL_Event;


class Scene4_Adv : public Scene {
private:

	class Camera* camera;
	class GameObject *gameObject;
	class Mesh *mesh;
	class Shader *shader;

public:
	explicit Scene4_Adv();
	virtual ~Scene4_Adv();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE4_ADV_H