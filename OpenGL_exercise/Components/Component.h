#pragma once


class Component {

public:
	virtual ~Component() = 0;
	virtual void Update() = 0;
};