#pragma once
class Time {
public:
	~Time();
	
	void Init();
	void Update(float time);

	static float DeltaTime();

	static Time* GetInstance();
private:

	Time();

	static Time* m_instance;

	float m_deltaTime;
	float m_prevTime;
	float m_currTime;
};

