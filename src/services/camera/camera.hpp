#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
	void reset(glm::vec2 u, glm::vec2 v);
	glm::mat4 getView();
	glm::vec3* getPosition();
	float* getYaw();
	float* getPitch();
	static Camera* getInstance();
	void look(float yaw, float pitch);
	void doRoll(float);
	void goFoward(float);
	void goBack(float);
	void goRight(float);
	void goLeft(float);
	void goUp(float);
	void goDown(float);
	void rotateAround(float angle);
	void requestReset();
	bool getResetRequest();
	void setResetRequest(bool);
	void Camera::update();
private:
	Camera();
	static Camera* instance;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;
	glm::mat4 view;
	float yaw;
	float pitch;
	float roll;
	float oldRoll;
	bool shouldReset = true;
};