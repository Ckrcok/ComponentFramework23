#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene5_Adv.h"
#include "GameObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Debug.h"
#include "Camera.h"
#include "SkyBox.h"
#include "Noise.h"


Scene5_Adv::Scene5_Adv(): camera(nullptr), mesh(nullptr), shader(nullptr), totalTime(0.0f){
	Debug::Info("Creating Scene5_Adv: ", __FILE__, __LINE__);
	camera = new Camera();	
}

Scene5_Adv::~Scene5_Adv() {
	if(camera) delete camera;	
}

bool Scene5_Adv::OnCreate() {

	noiseTextureID = CreateNoise3D();
	bool status = camera->getSkyBox()->loadSkyBox("textures/StarSkyboxPosx.png", "textures/StarSkyboxNegx.png",
												"textures/StarSkyboxPosy.png", "textures/StarSkyboxNegy.png",
												"textures/StarSkyboxPosz.png", "textures/StarSkyboxNegz.png");
	if (status == false) {
		return false;
	}
	if (ObjLoader::loadOBJ("meshes/Sphere.obj") == false) {
		return false;
	}
	mesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shader = new Shader("shaders/noiseVert.glsl", "shaders/turbulenceFrag_Adv.glsl");
	if (mesh == nullptr || shader == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}
	
	gameObject = new GameObject(mesh,shader,nullptr);
	gameObject->OnCreate();
	gameObject->setModelMatrix(MMath::scale(2.0f,2.0f,2.0f));
	return true;
}

void Scene5_Adv::HandleEvents(const SDL_Event& sdlEvent) {
	camera->HandleEvents(sdlEvent);
}

void Scene5_Adv::Update(const float deltaTime) {
	totalTime += deltaTime;
	offset.x += 0.001f;
	offset.y += 0.001f;
	offset.z -= 0.005f;
}

void Scene5_Adv::Render() const {
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
	//glUniform1f(gameObject->getShader()->getUniformID("time"), totalTime);
	glUniform3fv(gameObject->getShader()->getUniformID("offset"),1,offset);
	glBindTexture(GL_TEXTURE_3D, noiseTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, camera->getSkyBox()->getTextureID());
	gameObject->Render();
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindTexture(GL_TEXTURE_3D, 0);
	glUseProgram(0);
}


void Scene5_Adv::OnDestroy() {
	DeleteNoise3D();

}
