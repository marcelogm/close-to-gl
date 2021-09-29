#pragma once

#include "../../../services.hpp"
#include "../../../camera/camera.hpp"

class PhongIlluminationModel{
public:
	PhongIlluminationModel();
	glm::vec4 apply(glm::vec4 position, glm::vec4 normal);
private:

	float ambientStrength;
	float diffuseStrength;
	float specularStrength;

	glm::vec4 light;
	glm::vec4 camera;
	
	glm::vec4 color;
	glm::vec4 lightColor;
	glm::vec4 getReflection(glm::vec4 I, glm::vec4 normal);
	glm::vec4 getLightDirection(glm::vec4 position);
	glm::vec4 getAmbientLight();
	glm::vec4 getDiffuseLight(glm::vec4 normal, glm::vec4 direction);
	glm::vec4 getSpecularLight(glm::vec4 normal, glm::vec4 position, glm::vec4 direction);
}