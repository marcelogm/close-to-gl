#include "camera.hpp"

void Camera::reset(glm::vec2 u, glm::vec2 v, float fov) {
	auto uNorm = glm::distance(u.x, u.y);
	auto vNorm = glm::distance(v.x, v.y);

	auto x = glm::min(u.x, u.y) + (uNorm / 2.0f);
	auto y = glm::min(v.x, v.y) + (vNorm / 2.0f);
	auto z = glm::abs(glm::min(uNorm, vNorm) / glm::sin(fov / 2));

	this->position = glm::vec3(x, y, z);

	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->yaw = -90.0f;
	this->pitch = 0.0f;

	this->update();
}

glm::mat4 Camera::getView() {
	return this->view;
}

void Camera::update() {
	auto yawRadians = glm::radians(yaw);
	auto pitchRadians = glm::radians(pitch);

	front.x = glm::cos(yawRadians) * glm::cos(pitchRadians);
	front.y = glm::sin(pitchRadians);
	front.z = glm::sin(yawRadians) * glm::cos(pitchRadians);

	this->front = glm::normalize(this->front);
	this->right = glm::normalize(glm::cross(front, up));
	this->view = glm::lookAt(position, position + front, up);
}

void Camera::look(float yawOffset, float pitchOffset) {
	pitch += pitchOffset;
	yaw += yawOffset;
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}
	this->update();
}

void Camera::roll(float roll) {
	auto rotate = glm::rotate(glm::mat4(1.0f), glm::radians(roll), front);
	this->up = rotate * glm::vec4(up, 1.0f);
	this->update();
}

void Camera::goFoward(float speed) {
	position += front * speed;
	this->update();
}

void Camera::goBack(float speed) {
	position -= front * speed;
	this->update();
}

void Camera::goRight(float speed) {
	position += right * speed;
	this->update();
}

void Camera::goLeft(float speed) {
	position -= right * speed;
	this->update();
}

void Camera::goUp(float speed) {
	position += up * speed;
	this->update();
}

void Camera::goDown(float speed) {
	position -= up * speed;
	this->update();
}

void Camera::rotateAround(float x) {
	auto rotate = glm::rotate(glm::mat4(1.0f), glm::radians(x), this->up);
	this->position = rotate * glm::vec4(this->position, 1.0f);
	this->look(-x, 0.0f);
}

void Camera::requestReset() {
	this->shouldReset = true;
}

bool Camera::getResetRequest() {
	return this->shouldReset;
}

void Camera::setResetRequest(bool request) {
	shouldReset = request;
}

Camera* Camera::getInstance() {
	if (instance == nullptr) {
		instance = new Camera();
	}
	return instance;
}

Camera* Camera::instance = nullptr;

Camera::Camera() {
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->yaw = -90.0f;
	this->pitch = 0.0f;
}