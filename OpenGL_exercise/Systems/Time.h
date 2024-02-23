#pragma once



class Time {
private:
	float currentTime;
	float lastTime;

public:
	float deltaTime;

	Time();
	~Time();
	void Update();
	float GetTime();
};
