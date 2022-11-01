#include <glew.h>
#include <SDL.h>
#include "Debug.h"
#include "Scene1.h"
#include "GameObject.h"

#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Physics.h"

Scene1::Scene1() : meshPtr(nullptr), shaderPtr(nullptr), texturePtr(nullptr) {
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
}

Scene1::~Scene1() {}

bool Scene1::OnCreate() {
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
 
	lightPos0 = Vec3( 0.0, 5.0, 0.0);
	lightPos1 = Vec3(-5.0, 0.0, 0.0);
	if (ObjLoader::loadOBJ("meshes/CoronaVirus.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("shaders/multiPhongVert.glsl", "shaders/multiPhongFrag.glsl");

	gameObject = new GameObject(meshPtr,shaderPtr,nullptr);
	gameObject->setAngularVel(36.0f);
	return true;
}

void Scene1::HandleEvents(const SDL_Event &sdlEvent) {
	gameObject->HandleEvents(sdlEvent);
}

void Scene1::Update(const float deltaTime) {
	Physics::RigidBodyRotation(*gameObject,deltaTime);
	gameObject->Update(deltaTime);
}

void Scene1::Render() const {
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
	glUniform3fv(gameObject->getShader()->getUniformID("lightPos0"), 1, lightPos0);
	glUniform3fv(gameObject->getShader()->getUniformID("lightPos1"), 1, lightPos1);

	gameObject->Render();
	glUseProgram(0);
}


void Scene1::OnDestroy() {
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (gameObject) delete gameObject, gameObject = nullptr;
}
