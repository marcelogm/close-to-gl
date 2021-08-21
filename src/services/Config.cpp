#include "services.hpp"

Config::Config() {
};

Config* Config::getInstance() {
	if (instance == nullptr) {
		instance = new Config();
	}
	return instance;
}

Config* Config::instance = nullptr;

float* Config::getColor() {
	return this->color;
}

int* Config::getFOV() {
	return &this->fov;
}

int* Config::getZNear() {
	return &this->zNear;
}

int* Config::getZFar() {
	return &this->zFar;
}

bool* Config::getMove() {
	return &this->move;
}

bool* Config::getCW() {
	return &this->isCW;
}