#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
class SceneManager  {
public:
	
	SceneManager();
	~SceneManager();
	void Run();
	bool Initialize(std::string name_, int width_, int height_);
	void GetEvents();
	
	
private:
	/// Constants and enum are traditionally capitalized
	enum SCENE_NUMBER {
		SCENE0 = 0,
		SCENE0_ADV,
		SCENE1,
		SCENE1_ADV,
		SCENE2,
		SCENE2_ADV,
		SCENE3,
		SCENE3_ADV,
		SCENE4,
		SCENE4_ADV,
		SCENE5,
		SCENE5_ADV,
		SCENE6,
		SCENE6_ADV

	};

	class Scene* currentScene;
	class Timer* timer;
	class Window* window;

	unsigned int fps;
	bool isRunning;
	bool fullScreen;
	void BuildScene(SCENE_NUMBER scene_);
};


#endif // SCENEMANAGER_H