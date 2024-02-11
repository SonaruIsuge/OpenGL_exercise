#pragma once

#include <iostream>
#include <type_traits>
#include <list>
#include "../Shapes/Shape.h"
#include "..//Systems/Camera.h"
#include "../Components/Component.h"

using namespace std;

template <typename T>
concept IsComponent = is_base_of<Component, T>::value;


class Object {
protected:
	Camera* camera;
	list<Component*> components;

public:
	Shape* shape;

	vec3& position;
	vec3& rotation;
	vec3& scale;

	Object(Shape* shape, Camera* camera);
	virtual ~Object();
	void Update(float deltaTime);
	void SetParent(Object* object);
	void SetShape(Shape* shape);
	
	
	template <IsComponent T>
	T* GetComponent();

	template <IsComponent T>
	T* AddComponent();

	template <IsComponent T> 
	void RemoveComponent();
};