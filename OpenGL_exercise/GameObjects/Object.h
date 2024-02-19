#pragma once

#include <iostream>
#include <type_traits>
#include <vector>
#include "../Shapes/Shape.h"
#include "..//Systems/Camera.h"
#include "../Components/Component.h"
#include "../Tools/GameEnum.h"


template <typename T>
concept IsComponent = std::is_base_of<Component, T>::value;


class Object {
protected:
	std::vector<std::unique_ptr<Component>> components;

public:
	Camera* camera;
	Shape* shape;

	vec3& position;
	vec3& rotation;
	vec3& scale;

	Object(Shape* shape, Camera* camera);
	virtual ~Object();
	void Update(float deltaTime);
	void SetParent(Object* object);
	void SetShape(Shape* shape);
	void SetColor(vec4 color);


	template<IsComponent T>
	T* GetComponent() {
		for (auto&& component : components) {
			if(typeid(*component) == typeid(T))
				return dynamic_cast<T*>(component.get());
		}

		return nullptr;
	}


	template<IsComponent T, typename... Args>
	void AddComponent(Args&&... params) {
		components.emplace_back(std::make_unique<T>(std::forward<Args>(params)...));
	}


	template <IsComponent T>
	void RemoveComponent() {
		if (components.empty())
			return;

		components.erase(std::remove_if(components.begin(), components.end(),
			[](const auto& c) {
				return dynamic_cast<T*>(c.get()) != nullptr;
			}),
			components.end());
	}
};