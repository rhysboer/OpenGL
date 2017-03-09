#pragma once
class Time {
public:
	~Time();
	
	void Init();
	void Update(float time);

	static float DeltaTime();
	static double GetTime();

	static Time* GetInstance();
private:

	Time();

	static Time* m_instance;

	float m_time;

	float m_deltaTime;
	float m_prevTime;
	float m_currTime;
};

