#include "ObjectInteractHandler.h"

ObjectInteractHandler* ObjectInteractHandler::_instance = nullptr;

ObjectInteractHandler* ObjectInteractHandler::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ObjectInteractHandler;
	}
	return _instance;
}


ObjectInteractHandler::ObjectInteractHandler() {
	
}


ObjectInteractHandler::~ObjectInteractHandler() {

}


void ObjectInteractHandler::Update(float deltaTime) {

}



void ObjectInteractHandler::HandleCollide() {

}

