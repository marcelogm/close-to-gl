#include "close.hpp"

using namespace close;
using glm::normalize;

ColorShader::ColorShader() {
	this->config = Config::getInstance();
}

bool ColorShader::test() {
	return *config->getShading() != LIGHT_GOURAUD_ADS;
}

vec4 ColorShader::apply(glm::vec4 position, glm::vec4 normal) {
	const float* color = config->getColor();

	if (*config->getTextureUse() == 0) {
		return vec4(color[0], color[1], color[2], color[3]);
	} else {
		return vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

PhongIlluminationModel::PhongIlluminationModel() {
	const auto camera = Camera::getInstance();
	this->config = Config::getInstance();
	this->ambientStrength = config->getAmbientStrength();
	this->diffuseStrength = config->getDiffuseStrength();
	this->specularStrength = config->getSpecularStrength();
	this->light = config->getLightPosition();
	this->camera = camera->getPosition();
}

bool close::PhongIlluminationModel::test() {
	return *config->getShading() == LIGHT_GOURAUD_ADS;
}

vec3 close::PhongIlluminationModel::getLightColor() {
	const auto color = config->getLightColor();
	return vec3(color[0], color[1], color[2]);
}

vec3 close::PhongIlluminationModel::getObjectColor() {
	const auto color = config->getColor();
	return vec3(color[0], color[1], color[2]);
}

vec3 PhongIlluminationModel::getReflection(vec3* I, vec3* normal) {
	return *I - *normal * glm::dot(*normal, *I) * 2.f;
}

vec3 PhongIlluminationModel::getLightDirection(vec3* position) {
	return glm::normalize(*position - *this->light);
}

vec3 PhongIlluminationModel::getAmbientLight(vec3* color) {
	return *this->ambientStrength * *color;
}

vec3 PhongIlluminationModel::getDiffuseLight(vec3* normal, vec3* direction, vec3* color) {
	return *this->diffuseStrength * (glm::max)(glm::dot(*normal, *direction), 0.0f) * *color;
}

vec3 PhongIlluminationModel::getSpecularLight(vec3* normal, vec3* position, vec3* direction, vec3* color) {
	const auto viewDirection = *config->getCWModel() ? normalize(*position - *this->camera) : normalize(*this->camera - *position);
	const auto reflectionDirection = this->getReflection(&-(*direction), normal);
	const float spec = glm::pow(max(glm::dot(viewDirection, reflectionDirection), 0.0f), 10);
	return *this->specularStrength * spec * *color;
}

vec4 PhongIlluminationModel::apply(vec4 position, vec4 normal) {
	vec3 vPosition = vec3(position);
	vec3 vNormal = vec3(normal);

	auto lightColor = this->getLightColor();
	auto color = this->getObjectColor();
	auto N = glm::normalize(vNormal);
	auto direction = this->getLightDirection(&vPosition);
	
	const auto ambient = this->getAmbientLight(&lightColor);
	const auto diffuse = this->getDiffuseLight(&N, &direction, &lightColor);
	const auto specular = this->getSpecularLight(&N, &vPosition, &direction, &lightColor);
	const auto light = (ambient + diffuse + specular);

	vec3 out;
	if (*config->getTextureUse() == 0) {
		out = light * color;
	} else {
		out = light * vec3(1.0f, 1.0f, 1.0f);
	}
	
	return vec4(
		min(out.x, 1.0f),
		min(out.y, 1.0f),
		min(out.z, 1.0f),
		1.0f
	);
}
