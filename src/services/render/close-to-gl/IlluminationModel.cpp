#include "close.hpp"

using namespace close;

PhongIlluminationModel::PhongIlluminationModel() {
	auto config = Config::getInstance();
	auto camera = Camera::getInstance();

	this->ambientStrength = *config->getAmbientStrength();
	this->diffuseStrength = *config->getDiffuseStrength();
	this->specularStrength = *config->getSpecularStrength();
	
	this->light = glm::vec4(*config->getLightPosition(), 1.0f);
	this->camera = glm::vec4(*camera->getPosition(), 1.0f);
	
	float* pColor = config->getColor();
	float* pLight = config->getLightColor();
	this->color = glm::vec4(pColor[0], pColor[1], pColor[2], 1.0f);
	this->lightColor = glm::vec4(pLight[0], pLight[1], pLight[2], 1.0f);
}

glm::vec4 PhongIlluminationModel::getReflection(glm::vec4 I, glm::vec4 normal) {
	return I - normal * glm::dot(normal, I) * 2.f;
}

glm::vec4 PhongIlluminationModel::getLightDirection(glm::vec4 position) {
	return glm::normalize(this->light - position);
}

glm::vec4 PhongIlluminationModel::getAmbientLight() {
	return this->ambientStrength * this->lightColor;
}

glm::vec4 PhongIlluminationModel::getDiffuseLight(glm::vec4 normal, glm::vec4 direction) {
	return this->diffuseStrength * max(glm::dot(normal, direction), 0.0f) * this->lightColor;
}

glm::vec4 PhongIlluminationModel::getSpecularLight(glm::vec4 normal, glm::vec4 position, glm::vec4 direction) {
	glm::vec4 viewDirection = glm::normalize(this->camera - position);
	glm::vec4 reflectionDirection = this->getReflection(-direction, normal);
	return this->specularStrength * (float) glm::pow(max(glm::dot(viewDirection, reflectionDirection), 0.0f), 3) * this->lightColor;
}

glm::vec4 PhongIlluminationModel::apply(glm::vec4 position, glm::vec4 normal) {
	auto N = glm::normalize(normal);
	auto direction = this->getLightDirection(position);
	auto ambient = this->getAmbientLight();
	auto diffuse = this->getDiffuseLight(N, direction);
	auto specular = this->getSpecularLight(N, position, direction);
	auto light = (ambient + diffuse + specular);
	return light * color;
}
