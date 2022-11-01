#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene2.h"
#include "GameObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"
#include "Timer.h"
#include "Trackball.h"

Scene2::Scene2(): skull(nullptr),lEye(nullptr), rEye(nullptr), skullMesh(nullptr),shaderPtr(nullptr), skullTexture(nullptr) {
	trackball = nullptr;
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene2::~Scene2() {}

bool Scene2::OnCreate() {

	trackball = new Trackball();
	lightSource = Vec3(5.0f, 0.0f,0.0f);
	

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	cameraPos = Vec3(0.0f, 0.0f, 10.0f);
	viewMatrix = MMath::lookAt(cameraPos, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	
	
	buildSkull();
	buildEyes();

	
	skull->setModelMatrix(MMath::rotate(0.0f,Vec3(0.0f, 1.0f, 0.0f)));
	Matrix4 studioMaxCorrection = MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f));
	rEye->setModelMatrix(MMath::translate( 0.575f, 0.23f, 0.6f)  * MMath::scale(0.33f, 0.33f, 0.33f) * studioMaxCorrection);
	lEye->setModelMatrix(MMath::translate( -0.575f, 0.23f, 0.6f) * MMath::scale(0.33f, 0.33f, 0.33f) * studioMaxCorrection);
	return true;
}

void Scene2::HandleEvents(const SDL_Event &sdlEvent) {
	trackball->HandleEvents(sdlEvent);
}

void Scene2::Update(const float deltaTime) {
	skull->Update(deltaTime);
}

void Scene2::Render() const {

	skull->setModelMatrix(trackball->getMatrix4());
	/// Clear the screen
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	/// Draw your scene here
	GLuint program = skull->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(skull->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(skull->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE,viewMatrix);
	glUniform3fv(skull->getShader()->getUniformID("lightPos"), 1, lightSource);

	skull->Render();
	lEye->Render();
	rEye->Render();
	
	glUseProgram(0);
}


void Scene2::OnDestroy() {
	if (skullMesh) delete skullMesh, skullMesh = nullptr;
	if (skullTexture) delete skullTexture, skullTexture = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (skull) delete skull, skull = nullptr;
	if(trackball) delete trackball;
}





bool Scene2::buildSkull(){
	if (ObjLoader::loadOBJ("meshes/Skull.obj") == false) {
		return false;
	}
	skullMesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("shaders/texturePhongVert.glsl", "shaders/texturePhongFrag.glsl");
	skullTexture = new Texture();


	if (skullMesh == nullptr || shaderPtr == nullptr || skullTexture == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}


	if (skullTexture->LoadImage("textures/skull_texture.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}

	skull = new GameObject(nullptr, skullMesh, shaderPtr, skullTexture);
	if (skull == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	return true;
}

bool Scene2::buildEyes(){
	if (ObjLoader::loadOBJ("meshes/sphere.obj") == false) {
		return false;
	}
	eyeMesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	///shaderPtr = new Shader("shaders/texturePhongVert.glsl", "shaders/texturePhongFrag.glsl");
	eyeTexture = new Texture();
	if (eyeTexture == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}
	if (eyeTexture->LoadImage("textures/evilEye.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}
	lEye = new GameObject(skull, eyeMesh, shaderPtr, eyeTexture);
	rEye = new GameObject(skull, eyeMesh, shaderPtr, eyeTexture);
	if (lEye == nullptr || rEye == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	return true;
	
}