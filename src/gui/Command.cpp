#include "gui.hpp"

KeyCommandStrategy::KeyCommandStrategy() {
	this->camera = Camera::getInstance();
}

bool PitchUp::matches(int key, int action) {
	return action == GLFW_PRESS && key == GLFW_KEY_W;
};

void PitchUp::apply(float angle) {
	camera->look(0.0f, 10.0f);
};

bool PitchDown::matches(int key, int action) {
	return action == GLFW_PRESS && key == GLFW_KEY_S;
};

void PitchDown::apply(float angle) {
	camera->look(0.0f, -10.0f);
};

bool RollRight::matches(int key, int action) {
	return action == GLFW_PRESS && key == GLFW_KEY_T;
};

void RollRight::apply(float angle) {
	camera->roll(10.0f);
};

bool RollLeft::matches(int key, int action) {
	return action == GLFW_PRESS && key == GLFW_KEY_G;
};

void RollLeft::apply(float angle) {
	camera->roll(-10.0f);
};

bool YawLeft::matches(int key, int action) {
	return action == GLFW_PRESS && key == GLFW_KEY_A;
};

void YawLeft::apply(float angle) {
	camera->look(-10.0f, 0.0f);
};

bool YawRight::matches(int key, int action) {
	return action == GLFW_PRESS && key == GLFW_KEY_D;
};

void YawRight::apply(float angle) {
	camera->look(10.0f, 0.0f);
};

bool Reset::matches(int key, int action) {
	return action == GLFW_PRESS && key == GLFW_KEY_R;
};

void Reset::apply(float angle) {
	camera->requestReset();
};

bool RotateLeft::matches(int key, int action) {
	return action == GLFW_PRESS && key == GLFW_KEY_4;
};

void RotateLeft::apply(float angle) {
	camera->rotateAround(10.0f);
};

bool RotateRight::matches(int key, int action) {
	//return action == GLFW_PRESS && key == GLFW_KEY_RIGHT;
	return false;
};

void RotateRight::apply(float angle) {
	//camera->rotateAround(-10.0f);
};

bool MoveLeft::matches(int key, int action) {
	return action == GLFW_PRESS && key == GLFW_KEY_LEFT;
};

void MoveLeft::apply(float angle) {
	camera->goLeft(100.0f);
};

bool MoveRight::matches(int key, int action) {
	return action == GLFW_PRESS && key == GLFW_KEY_RIGHT;
};

void MoveRight::apply(float angle) {
	camera->goRight(100.0f);
};


bool MoveFront::matches(int key, int action) {
	return action == GLFW_PRESS && key == GLFW_KEY_UP;
};

void MoveFront::apply(float angle) {
	camera->goFoward(100.0f);
};


bool MoveBack::matches(int key, int action) {
	return action == GLFW_PRESS && key == GLFW_KEY_DOWN;
};

void MoveBack::apply(float angle) {
	camera->goBack(100.0f);
};


KeyStrategyService::KeyStrategyService() {
	strategies = new std::vector<KeyCommandStrategy*>();
	strategies->push_back(new PitchUp());
	strategies->push_back(new PitchDown());
	strategies->push_back(new RollLeft());
	strategies->push_back(new RollRight());
	strategies->push_back(new YawLeft());
	strategies->push_back(new YawRight());
	strategies->push_back(new Reset());
	strategies->push_back(new RotateLeft());
	strategies->push_back(new RotateRight());
	strategies->push_back(new MoveFront());
	strategies->push_back(new MoveBack());
	strategies->push_back(new MoveRight());
	strategies->push_back(new MoveLeft());
}

std::vector<KeyCommandStrategy*>* KeyStrategyService::getKeyStrategies() {
	return strategies;
}

KeyStrategyService* KeyStrategyService::getInstance() {
	if (instance == nullptr) {
		instance = new KeyStrategyService();
	}
	return instance;
}

KeyStrategyService* KeyStrategyService::instance = nullptr;