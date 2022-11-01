#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene4_Adv.h"
#include "GameObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Debug.h"
#include "Camera.h"
#include "SkyBox.h"


Scene4_Adv::Scene4_Adv(): camera(nullptr), gameObject(nullptr), mesh(nullptr), shader(nullptr) {
	Debug::Info("Creating Scene4_Adv: ", __FILE__, __LINE__);
	camera = new Camera();	
}

Scene4_Adv::~Scene4_Adv() {
	if(camera) delete camera;	
}

bool Scene4_Adv::OnCreate() {

	bool status = camera->getSkyBox()->loadSkyBox("textures/posx.jpg", "textures/negx.jpg",
												"textures/posy.jpg", "textures/negy.jpg",
												"textures/posz.jpg", "textures/negz.jpg");
	if (status == false) {
		return false;
	}

	if (ObjLoader::loadOBJ("meshes/Sphere.obj") == false) {
		return false;
	}
	mesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shader = new Shader("shaders/reflectionVert.glsl", "shaders/reflectionFrag.glsl");
	if (mesh == nullptr || shader == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}
	
	gameObject = new GameObject(mesh,shader,nullptr);
	gameObject->OnCreate();
	gameObject->setModelMatrix(MMath::scale(2.0f,2.0f,2.0f));
	return true;
}

void Scene4_Adv::HandleEvents(const SDL_Event& sdlEvent) {
	camera->HandleEvents(sdlEvent);
}

void Scene4_Adv::Update(const float deltaTime) {

}

void Scene4_Adv::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	/// Draw your scene here
	camera->Render();

	glUseProgram(gameObject->getShader()->getProgram());
	glUniformMatrix4fv(gameObject->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(gameObject->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix() * camera->getCameraRotationMatrix());

	glBindTexture(GL_TEXTURE_CUBE_MAP, camera->getSkyBox()->getTextureID());
	gameObject->Render();
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glUseProgram(0);
}


void Scene4_Adv::OnDestroy() {

}
