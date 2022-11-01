#ifndef SCENE3_H
#define SCENE3_H
#include "Scene.h"


/// Forward declarations 
union SDL_Event;


class Scene3 : public Scene {
private:

	class Camera* camera;


public:
	explicit Scene3();
	virtual ~Scene3();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE3_H