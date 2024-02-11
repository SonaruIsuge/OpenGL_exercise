#pragma once


class Component {
protected:
	bool isActive;

public:
	virtual ~Component() = 0;
	virtual void Update() = 0;
	virtual void SetActive(bool active) { isActive = active; }
	virtual bool IsActive() { return isActive; }
};