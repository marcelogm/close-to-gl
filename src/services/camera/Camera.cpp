#include "camera.hpp"

void Camera::reset(glm::vec2 u, glm::vec2 v) {
	const auto uNorm = glm::distance(u.x, u.y);
	const auto vNorm = glm::distance(v.x, v.y);

	const auto x = glm::min(u.x, u.y) + (uNorm / 2.0f);
	const auto y = glm::min(v.x, v.y) + (vNorm / 2.0f);
	const auto z = glm::abs(glm::min(uNorm, vNorm) / glm::sin(glm::radians(45.0f) / 2));

	this->position = glm::vec3(x, y, z);

	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->yaw = -90.0f;
	this->pitch = 0.0f;

	this->update();
	this->setResetRequest(false);
}

glm::mat4 Camera::getView() {
	return this->view;
}

void Camera::update() {
	const auto yawRadians = glm::radians(yaw);
	const auto pitchRadians = glm::radians(pitch);

	front.x = glm::cos(yawRadians) * glm::cos(pitchRadians);
	front.y = glm::sin(pitchRadians);
	front.z = glm::sin(yawRadians) * glm::cos(pitchRadians);

	this->front = glm::normalize(this->front);
	this->right = glm::normalize(glm::cross(front, up));
	
	const glm::vec3 eye = position;
	const glm::vec3 target = position + front;
	const glm::vec3 n = glm::normalize(eye - target);
	const glm::vec3 u = glm::normalize(glm::cross(up, n));
	const glm::vec3 v = glm::cross(n, u);
	const glm::vec3 O = eye;
	this->view = glm::mat4(
					u.x,			v.x,			  n.x, 0.f,
					u.y,			v.y,		      n.y, 0.f,
					u.z,			v.z,			  n.z, 0.f,
		-glm::dot(O, u), -glm::dot(O, v), -glm::dot(O, n), 1.f
	);
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

void Camera::doRoll(float roll) {
	this->oldRoll = this->roll;
	this->roll = roll;
	const auto rotate = glm::rotate(glm::mat4(1.0f), glm::radians(this->oldRoll - this->roll), front);
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

void Camera::rotateAround(float angle) {
	const auto rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), this->up);
	this->position = rotation * glm::vec4(this->position, 1.0f);
	this->look(-angle, 0.0f);
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
	this->roll = 0.0f;
}

float* Camera::getYaw() {
	return &this->yaw;
}

float* Camera::getPitch() {
	return &this->pitch;
}

glm::vec3* Camera::getPosition() {
	return &this->position;
}