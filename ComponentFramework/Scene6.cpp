#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene6.h"
#include "GameObject.h"
#include "ObjLoader.h"
#include "Shader.h"
#include "Texture.h"
#include "Debug.h"
#include "Camera.h"
#include "SkyBox.h"
#include "Particles.h"


Scene6::Scene6(): camera(nullptr), mesh(nullptr), shader(nullptr), totalTime(0.0f){
	Debug::Info("Creating Scene6: ", __FILE__, __LINE__);
	camera = new Camera();	
}

Scene6::~Scene6() {
	if(camera) delete camera;	
}

bool Scene6::OnCreate() {
	particles = new Particles(10);
	
	bool status = camera->getSkyBox()->loadSkyBox("textures/posx.jpg", "textures/negx.jpg",
												"textures/posy.jpg", "textures/negy.jpg",
												"textures/posz.jpg", "textures/negz.jpg");
	if (status == false) {
		return false;
	}
	
	
	
	shader = new Shader("shaders/particlesVert.glsl", "shaders/particlesFrag.glsl");
	
	return true;
}

void Scene6::HandleEvents(const SDL_Event& sdlEvent) {
	camera->HandleEvents(sdlEvent);
}

void Scene6::Update(const float deltaTime) {
	totalTime += deltaTime/20.0f;
}

void Scene6::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	/// Draw your scene here
	///camera->Render();

	glUseProgram(shader->getProgram());
	glUniformMatrix4fv(shader->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(shader->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix() * camera->getCameraRotationMatrix());
	glUniform1f(shader->getUniformID("totalTime"), totalTime);
	particles->Render();
	glUseProgram(0);
}


void Scene6::OnDestroy() {
	delete particles;
}
