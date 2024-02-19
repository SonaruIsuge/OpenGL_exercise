#include "Object.h"


Object::Object(Shape* shape, Camera* camera) : position(shape->position), rotation(shape->rotation), scale(shape->scale) {
	this->camera = camera;
	this->shape = shape;

	shape->Init(this->camera->GetViewMatrix(), this->camera->GetProjMatrix());
}


Object::~Object() {
	if (shape != nullptr) delete shape;
}


void Object::Update(float deltaTime) {
	for (auto& c : components) {
		c->Update(deltaTime);
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


void Object::SetColor(vec4 color) {
	shape->SetSingleColor(color);
}
