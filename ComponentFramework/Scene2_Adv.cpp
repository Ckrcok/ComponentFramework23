#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene2_Adv.h"
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

Scene2_Adv::Scene2_Adv(): skull(nullptr),lEye(nullptr), rEye(nullptr), eyeTexture(nullptr),
			skullMesh(nullptr),shaderPtr(nullptr), skullTexture(nullptr),eyeMesh(nullptr) {
	trackball = nullptr; /// Just another way to init a variable
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene2_Adv::~Scene2_Adv() {}

bool Scene2_Adv::OnCreate() {

	trackball = new Trackball();
	lightSource = Vec3(5.0f, 0.0f,0.0f);
	

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	cameraPos = Vec3(0.0f, 0.0f, 10.0f);
	viewMatrix = MMath::lookAt(cameraPos, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	
	/// I put these in separate function just to keep things clean
	buildSkull();
	buildEyes();

	
	skull->setModelMatrix(MMath::rotate(0.0f,Vec3(0.0f, 1.0f, 0.0f)));
	Matrix4 studioMaxCorrection = MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f));
	float eyeRot = tan(0.575f / viewMatrix[14]) / DEGREES_TO_RADIANS;
	rEye->setModelMatrix(MMath::translate( 0.575f, 0.23f, 0.6f) * MMath::rotate(eyeRot, Vec3(0.0f, 1.0f, 0.0f)) * MMath::scale(0.33f, 0.33f, 0.33f) * studioMaxCorrection);
	lEye->setModelMatrix(MMath::translate( -0.575f, 0.23f, 0.6f) * MMath::rotate(-eyeRot, Vec3(0.0f, 1.0f, 0.0f)) * MMath::scale(0.33f, 0.33f, 0.33f) * studioMaxCorrection);
	return true;
}

void Scene2_Adv::HandleEvents(const SDL_Event &sdlEvent) {
	static float eyeRot;
	trackball->HandleEvents(sdlEvent);
	if(sdlEvent.type == SDL_USEREVENT){
		printf("%s\n",(char*)sdlEvent.user.data1);	
	}

	if (sdlEvent.type == SDL_KEYDOWN){	
		switch(sdlEvent.key.keysym.scancode){
		case SDL_SCANCODE_UP:
			cameraPos.z += 0.2f;
			viewMatrix = MMath::lookAt(cameraPos, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
			eyeRot = atan(0.575f / cameraPos.z) / DEGREES_TO_RADIANS;
			printf("%f\n", eyeRot);
			break;

		case SDL_SCANCODE_DOWN:
			cameraPos.z -= 0.2f;
			eyeRot = atan(0.575f / cameraPos.z) / DEGREES_TO_RADIANS;
			viewMatrix = MMath::lookAt(cameraPos, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
			printf("%f\n", eyeRot);
			break;

		default:
			break;
		}
		
	}
	Matrix4 studioMaxCorrection = MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f));
	rEye->setModelMatrix(MMath::translate(0.575f, 0.23f, 0.6f) * MMath::transpose(trackball->getMatrix4()) * MMath::rotate(-eyeRot,Vec3(0.0f,1.0f,0.0f)) * MMath::scale(0.33f, 0.33f, 0.33f) * studioMaxCorrection);
	lEye->setModelMatrix(MMath::translate(-0.575f, 0.23f, 0.6f) * MMath::transpose(trackball->getMatrix4()) * MMath::rotate(eyeRot, Vec3(0.0f, 1.0f, 0.0f)) * MMath::scale(0.33f, 0.33f, 0.33f) * studioMaxCorrection);
}

void Scene2_Adv::Update(const float deltaTime) {
	skull->Update(deltaTime);
	static float rotation = 0.0f;
	rotation += 0.5f;
	
	
}

void Scene2_Adv::Render() const {
	skull->setModelMatrix(trackball->getMatrix4());


	/// Clear the screen
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
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


void Scene2_Adv::OnDestroy() {
	if (skullMesh) delete skullMesh, skullMesh = nullptr;
	if (skullTexture) delete skullTexture, skullTexture = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (skull) delete skull, skull = nullptr;
	if(trackball) delete trackball;
}





bool Scene2_Adv::buildSkull(){
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

bool Scene2_Adv::buildEyes(){
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