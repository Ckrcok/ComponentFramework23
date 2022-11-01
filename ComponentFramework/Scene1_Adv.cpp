#include <glew.h>
#include <SDL.h>
#include "Debug.h"
#include "Scene1_Adv.h"
#include "GameObject.h"

#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Physics.h"

Scene1_Adv::Scene1_Adv() : gameObject(nullptr), meshPtr(nullptr), shaderPtr(nullptr), texturePtr(nullptr) {
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
}

Scene1_Adv::~Scene1_Adv() {}

bool Scene1_Adv::OnCreate() {
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	lightPos.push_back(Vec3(5.0f, 0.0f, 0.0f));
	lightPos.push_back(Vec3(-5.0f, 0.0f, 0.0f));
	lightPos.push_back(Vec3(0.0f, 5.0f, 0.0f));
	lightDiffuse.push_back(Vec4(0.6f, 0.1f, 0.1f, 0.0f));
	lightDiffuse.push_back(Vec4(0.1f, 0.6f, 0.1f, 0.0f));
	lightDiffuse.push_back(Vec4(0.1f, 0.1f, 0.6f, 0.0f));
	lightSpecular.push_back(Vec4(0.6f, 0.0f, 0.0f, 0.0f));
	lightSpecular.push_back(Vec4(0.0f, 0.6f, 0.0f, 0.0f));
	lightSpecular.push_back(Vec4(0.0f, 0.0f, 0.6f, 0.0f));

	if (ObjLoader::loadOBJ("meshes/CoronaVirus.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("shaders/multiPhongVert_Adv.glsl", "shaders/multiPhongFrag_Adv.glsl");

	gameObject = new GameObject(meshPtr,shaderPtr,nullptr);
	gameObject->setAngularVel(36.0f);
	return true;
}

void Scene1_Adv::HandleEvents(const SDL_Event &sdlEvent) {
	gameObject->HandleEvents(sdlEvent);
}

void Scene1_Adv::Update(const float deltaTime) {
	Physics::RigidBodyRotation(*gameObject,deltaTime);
	gameObject->Update(deltaTime);
}

void Scene1_Adv::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	/// Draw your scene here
	GLuint program = gameObject->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(gameObject->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(gameObject->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniform3fv(gameObject->getShader()->getUniformID("lightPos[0]"), lightPos.size(), lightPos[0]);
	glUniform4fv(gameObject->getShader()->getUniformID("lightDiffuse[0]"), lightDiffuse.size(), lightDiffuse[0]);
	glUniform4fv(gameObject->getShader()->getUniformID("lightSpecular[0]"), lightSpecular.size(), lightSpecular[0]);
	glUniform1i(gameObject->getShader()->getUniformID("numLights"), lightPos.size());
	gameObject->Render();
	glUseProgram(0);
}


void Scene1_Adv::OnDestroy() {
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (gameObject) delete gameObject, gameObject = nullptr;
}
