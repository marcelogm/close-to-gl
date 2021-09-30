#include "services.hpp"

Config::Config() {
	program = 0;
	texture = 0;
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

float* Config::getLightColor() {
	return this->lightColor;
}

float* Config::getAmbientStrength() {
	return &this->ambientStrength;
}

float* Config::getDiffuseStrength() {
	return &this->diffuseStrength;
}

float* Config::getSpecularStrength() {
	return &this->specularStrength;
}

int* Config::getXFOV() {
	return &this->xfov;
}

int* Config::getYFOV() {
	return &this->yfov;
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

float* Config::getSensibility() {
	return &this->sensibility;
}

float* Config::getMouseSensibility() {
	return &this->mouseSensibility;
}

bool* Config::getMouseStatus() {
	return &this->mouseStatus;
}

int* Config::getWindowHeight() {
	return &this->windowHeight;
}

int* Config::getWindowWidth() {
	return &this->windowWidth;
}

int* Config::getRenderMode() {
	return &this->renderMode;
}

bool* Config::getOpenGLUse() {
	return &this->useOpenGL;
}

int* Config::getShading() {
	return &this->shading;
}

glm::vec3* Config::getLightPosition() {
	return &this->lightPosition;
}

GLuint* Config::getCloseToGLProgramId() {
	return &this->program;
}

GLuint* Config::getCloseToGLTextureId() {
	return &this->texture;
}

void Config::reset() {
	yfov = 45;
	xfov = ((float)this->windowWidth / (float)this->windowHeight) * yfov;
	zNear = 1;
	zFar = 5000;
	lightPosition = glm::vec3(0.0f, 3.0f, 0.0f);
}