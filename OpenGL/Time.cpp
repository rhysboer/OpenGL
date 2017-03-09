#include "Time.h"

Time* Time::m_instance = nullptr;

Time::Time() {
	m_currTime	= 0.0f;
	m_prevTime	= 0.0f;
	m_deltaTime	= 0.0f;
}

Time::~Time() {
	delete m_instance;
}

void Time::Init() {
	if(m_instance == nullptr) {
		m_instance = new Time();
	}
}

void Time::Update(float time) {
	if(m_instance == nullptr)
		m_instance = new Time();

	m_instance->m_currTime = time;

	m_instance->m_deltaTime = m_instance->m_currTime - m_instance->m_prevTime;
	m_instance->m_prevTime = m_instance->m_currTime;
}

float Time::DeltaTime() {
	return GetInstance()->DeltaTime();
}

Time * Time::GetInstance() {
	return m_instance;
}
