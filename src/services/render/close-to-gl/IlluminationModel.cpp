#include "close.hpp"

using namespace close;

PhongIlluminationModel::PhongIlluminationModel() {
	auto config = Config::getInstance();
	auto camera = Camera::getInstance();

	this->ambientStrength = *config->getAmbientStrength();
	this->diffuseStrength = *config->getDiffuseStrength();
	this->specularStrength = *config->getSpecularStrength();
	
	this->light = *config->getLightPosition();
	this->camera = *camera->getPosition();
	
	float* pColor = config->getColor();
	float* pLight = config->getLightColor();
	this->color = glm::vec3(pColor[0], pColor[1], pColor[2]);
	this->lightColor = glm::vec3(pLight[0], pLight[1], pLight[2]);
}

glm::vec3 PhongIlluminationModel::getReflection(glm::vec3 I, glm::vec3 normal) {
	return I - normal * glm::dot(normal, I) * 2.f;
}

glm::vec3 PhongIlluminationModel::getLightDirection(glm::vec3 position) {
	return glm::normalize(this->light - position);
}

glm::vec3 PhongIlluminationModel::getAmbientLight() {
	return this->ambientStrength * this->lightColor;
}

glm::vec3 PhongIlluminationModel::getDiffuseLight(glm::vec3 normal, glm::vec3 direction) {
	return this->diffuseStrength * max(glm::dot(normal, direction), 0.0f) * this->lightColor;
}

glm::vec3 PhongIlluminationModel::getSpecularLight(glm::vec3 normal, glm::vec3 position, glm::vec3 direction) {
	glm::vec3 viewDirection = glm::normalize(this->camera - position);
	glm::vec3 reflectionDirection = this->getReflection(-direction, normal);
	return this->specularStrength * glm::pow(max(glm::dot(viewDirection, reflectionDirection), 0.0f), 3.0f) * this->lightColor;
}

glm::vec4 PhongIlluminationModel::apply(glm::vec4 position, glm::vec4 normal) {
	auto N = glm::normalize(normal);
	auto direction = this->getLightDirection(position);
	auto ambient = this->getAmbientLight();
	auto diffuse = this->getDiffuseLight(N, direction);
	auto specular = this->getSpecularLight(N, position, direction);
	auto out = color * (ambient + diffuse + specular);
	return glm::vec4(
		min(out.x, 1.0f),
		min(out.y, 1.0f),
		min(out.z, 1.0f),
		1.0f
	);
}
