#include "LightManager.h"
#include "Light.h"

LightManager* LightManager::m_instance = nullptr;

LightManager::LightManager() {
}

LightManager::~LightManager() {
}

LightManager * LightManager::GetInstance() {
	if(m_instance == nullptr)
		m_instance = new LightManager();

	return m_instance;
}

void LightManager::Destroy() {
	if(m_instance != nullptr)
		delete m_instance;

	m_instance = nullptr;  
}

void LightManager::AddLight(Light & light) {
	GetInstance()->m_lights.push_back(&light);
}

void LightManager::Draw(Camera camera) {
	// LightManager* lm = GetInstance();
	// int size = lm->m_lights.size();
	// 
	// for(int i = 0; i < size; ++i) {
	// 	lm->m_lights[i]->Draw(camera.GetProjectionView());
	// }
}
