#include "Object.h"


Object::Object(Shape* shape, Camera* camera) : position(shape->position), rotation(shape->rotation), scale(shape->scale) {
	this->camera = camera;

	this->shape = shape;
	shape->Init(vec4(1.0f, 1.0f, 1.0f, 1.0f), this->camera->GetViewMatrix(), this->camera->GetProjMatrix());
}


Object::~Object() {
	if (shape != nullptr) delete shape;

	for (auto it = components.begin(); it != components.end(); ++it) {
		delete* it;
	}
	components.clear();
}


void Object::Update(float deltaTime) {
	for (Component* c : components) {
		c->Update();
	}

	shape->Draw();
}


void Object::SetParent(Object* object) {
	shape->parent = object->shape;
}


void Object::SetShape(Shape* shape) {
	if (this->shape != nullptr) 
		delete this->shape;

	this->shape = shape;
}



template <IsComponent T> 
T* Object::GetComponent() {
	for (Component* c : components) {
		if (dynamic_cast<T*>(c) != nullptr) {
			return dynamic_cast<T*>(c);
		}
	}
	return nullptr;
}


template <IsComponent T> 
T* Object::AddComponent() {
	components.push_back(new T());
	return components.end();
}


template <IsComponent T>
void Object::RemoveComponent() {
	for (Component* c : components) {
		if (dynamic_cast<T*>(c) != nullptr) {
			delete *c;
			components.erase(c);
		}
	}
}