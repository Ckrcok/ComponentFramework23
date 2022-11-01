#ifndef CAMERA_H
#define CAMERA_H
#include "GameObject.h"
#include "Matrix.h"
#include "Trackball.h"
#include "SkyBox.h"

using namespace MATH;
class Camera : public Object {
private:
	Matrix4 projectionMatrix;

	Matrix4 viewMatrix;
	Matrix4 rotationMatrix;
	Matrix4 translationMatrix;


	SkyBox* skybox;
	Trackball* trackball;
public:
	Camera();
	~Camera();
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void HandleEvents(const SDL_Event& event) override;
	void Render() const override;
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getViewMatrix() { return viewMatrix; }
	Matrix4 getCameraRotationMatrix() { return trackball->getMatrix4(); }
	SkyBox* getSkyBox() { return skybox; }

};
#endif

