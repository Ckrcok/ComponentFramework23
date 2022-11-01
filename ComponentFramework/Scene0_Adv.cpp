#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene0_Adv.h"
#include "GameObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"
#include "Timer.h"
#include "MMath.h"
using namespace MATH;

Scene0_Adv::Scene0_Adv():gameObject(nullptr), meshPtr(nullptr), shaderPtr(nullptr), texturePtr(nullptr) {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0_Adv::~Scene0_Adv() {}

bool Scene0_Adv::OnCreate() {
	lightSource = Vec3(0.0f, 0.0f, 0.0f);
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));


	if (ObjLoader::loadOBJ("meshes/Mario.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("shaders/texturePhongVert.glsl", "shaders/texturePhongFrag.glsl");
	texturePtr = new Texture();
	if (meshPtr == nullptr || shaderPtr == nullptr || texturePtr == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}


	if (texturePtr->LoadImage("textures/mario_main.png") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}

	gameObject = new GameObject(meshPtr, shaderPtr, texturePtr);
	if (gameObject == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	gameObject->setAngularVel(25.0f);
	return true;
}

void Scene0_Adv::HandleEvents(const SDL_Event& sdlEvent) {
	if (sdlEvent.type == SDL_USEREVENT) {
		printf("%d: %s\n", (int)sdlEvent.user.data1, (char*)sdlEvent.user.data2);
	}
}

void Scene0_Adv::Update(const float deltaTime) {
	static float rotation = 0.0f;
	rotation += 1.0f;
	gameObject->setModelMatrix(MMath::rotate(rotation, Vec3(0.0f, 1.0f, 0.0f)));
	gameObject->Update(deltaTime);
}

void Scene0_Adv::Render() const {
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
	glUniform3fv(gameObject->getShader()->getUniformID("lightPos"), 1, lightSource);

	gameObject->Render();

	glUseProgram(0);
}


void Scene0_Adv::OnDestroy() {
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (gameObject) delete gameObject, gameObject = nullptr;
}
