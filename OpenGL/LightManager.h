#pragma once
#include <vector>
#include "Camera.h"

class Light;
class LightManager {
public:
	~LightManager();

	static LightManager* GetInstance();
	static void Destroy();

	static void AddLight(Light& light);
	//static void RemoveLight(Light& light);

	const static std::vector<Light*> GetLightVector();

	static void Draw(Camera camera);
private:
	LightManager();

	static LightManager* m_instance;
	std::vector<Light*> m_lights;
};

