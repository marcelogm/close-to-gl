#include "services.hpp"

glm::mat4 ProjectionFromConfig::get() {
	float xFov = *config->getXFOV();
	float yFov = *config->getYFOV();
	float zfar = *this->config->getZFar();
	float zNear = *this->config->getZNear();
	float height = glm::tan(glm::radians(yFov / 2)) * zNear;
	float width = glm::tan(glm::radians(xFov / 2)) * zNear;
	return glm::frustum(-width, width, -height, height, zNear, zfar);
}

ProjectionFromConfig::ProjectionFromConfig() {
	this->config = Config::getInstance();
}
;