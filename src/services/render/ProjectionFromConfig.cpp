#include "render.hpp"

using namespace renderer;

glm::mat4 ProjectionFromConfig::get() {
	float xFov = *config->getXFOV();
	float yFov = *config->getYFOV();
	float f = *this->config->getZFar();
	float n = *this->config->getZNear();
	float t = glm::tan(glm::radians(yFov / 2)) * n;
	float b = -t;
	float r = glm::tan(glm::radians(xFov / 2)) * n;
	float l = -r;

	return glm::mat4(
		(2 * n) / (r - l),                 0,                        0,  0,
		                0, (2 * n) / (t - b),                        0,  0,
		(r + l) / (r - l), (t + b) / (t - b),      -((f + n) / (f -n)), -1,
		                0,                 0, -((2 * f * n) / (f - n)),  0
	);
}

ProjectionFromConfig::ProjectionFromConfig() {
	this->config = Config::getInstance();
}
;