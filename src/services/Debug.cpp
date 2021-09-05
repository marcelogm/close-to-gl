#include "services.hpp"

Debug::Debug() {
};

Debug* Debug::getInstance() {
	if (instance == nullptr) {
		instance = new Debug();
	}
	return instance;
}

void Debug::countFrame() {
	currentFrameTime = glfwGetTime();
	timeFrameDiff = currentFrameTime - lastFrameTime;
	frameCounter++;
	if (timeFrameDiff >= 1.0 / 30.0) {
		framerate = ((1.0 / timeFrameDiff) * frameCounter);
		frametime = (timeFrameDiff / frameCounter) * 1000;
		lastFrameTime = currentFrameTime;
		frameCounter = 0;
	}
}

double Debug::getFramerate() {
	return this->framerate;
}

double Debug::getFrametime() {
	return this->frametime;
}

Debug* Debug::instance = nullptr;