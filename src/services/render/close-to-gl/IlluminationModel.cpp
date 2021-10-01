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
	this->color = vec3(pColor[0], pColor[1], pColor[2]);
	this->lightColor = vec3(pLight[0], pLight[1], pLight[2]);
}

vec3 PhongIlluminationModel::getReflection(vec3 I, vec3 normal) {
	return I - normal * glm::dot(normal, I) * 2.f;
}

vec3 PhongIlluminationModel::getLightDirection(vec3 position) {
	return glm::normalize(this->light - position);
}

vec3 PhongIlluminationModel::getAmbientLight() {
	return this->ambientStrength * this->lightColor;
}

vec3 PhongIlluminationModel::getDiffuseLight(vec3 normal, vec3 direction) {
	return this->diffuseStrength * max(glm::dot(normal, direction), 0.0f) * this->lightColor;
}

vec3 PhongIlluminationModel::getSpecularLight(vec3 normal, vec3 position, vec3 direction) {
	vec3 viewDirection = glm::normalize(position - this->camera);
	vec3 reflectionDirection = this->getReflection(-direction, normal);
	float spec = glm::pow(max(glm::dot(viewDirection, reflectionDirection), 0.0f), 10);
	return this->specularStrength * spec * this->lightColor;
}

vec3 PhongIlluminationModel::apply(vec3 position, vec3 normal) {
	auto N = glm::normalize(normal);
	auto direction = this->getLightDirection(position);
	auto ambient = this->getAmbientLight();
	auto diffuse = this->getDiffuseLight(N, direction);
	auto specular = this->getSpecularLight(N, position, direction);
	auto out = (ambient + diffuse + specular) * color;
	return vec3(
		min(out.x, 1.0f),
		min(out.y, 1.0f),
		min(out.z, 1.0f)
	);
}
