#include "camera.hpp"

void Camera::reset(glm::vec2 u, glm::vec2 v, float fov) {
	auto uNorm = glm::distance(u.x, u.y);
	auto vNorm = glm::distance(v.x, v.y);

	auto x = glm::min(u.x, u.y) + (uNorm / 2.0f);
	auto y = glm::min(v.x, v.y) + (vNorm / 2.0f);
	auto z = glm::abs(glm::min(uNorm, vNorm) / glm::sin(fov / 2));

	this->position = glm::vec3(x, y, z);
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->view = glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getView() {
	return this->view;
}

// yaw
void Camera::lookRight() {
	this->front = glm::mat3(glm::rotate(0.05f, this->up)) * this->front;
	this->view = glm::lookAt(position, position + front, up);
}

void Camera::lookLeft() {
	this->front = glm::mat3(glm::rotate(-0.05f, this->up)) * this->front;
	this->view = glm::lookAt(position, position + front, up);
}

// pitch
void Camera::lookUp() {
	glm::vec3 rotate = glm::cross(this->front, this->up);
	this->front = glm::mat3(glm::rotate(0.05f, rotate)) * this->front;
	this->view = glm::lookAt(position, position + front, up);
}

void Camera::lookDown() {
	glm::vec3 rotate = glm::cross(this->front, this->up);
	this->front = glm::mat3(glm::rotate(-0.05f, rotate)) * this->front;
	this->view = glm::lookAt(position, position + front, up);
}

void Camera::requestReset() {
	this->shouldReset = true;
}

Camera* Camera::getInstance() {
	if (instance == nullptr) {
		instance = new Camera();
	}
	return instance;
}

Camera* Camera::instance = nullptr;

Camera::Camera() {

}