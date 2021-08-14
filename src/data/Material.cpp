#include "data.hpp"

using namespace data;

Material::Material(const Material& material) {
	ambientColor = new glm::vec3(*material.ambientColor);
	diffuseColor = new glm::vec3(*material.diffuseColor);
	specularColor = new glm::vec3(*material.specularColor);
	shineCoeff = material.shineCoeff;
};

Material::Material(glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular, float shine) {
	this->ambientColor = ambient;
	this->diffuseColor = diffuse;
	this->specularColor = specular;
	this->shineCoeff = shine;
};

glm::vec3* Material::getAmbientColor() {
	return ambientColor;
}

glm::vec3* Material::getDiffuseColor() {
	return diffuseColor;
}

glm::vec3* Material::getSpecularColor() {
	return specularColor;
}

float Material::getShineCoeff() {
	return shineCoeff;
}

Material::~Material() {
	delete ambientColor;
	delete diffuseColor;
	delete specularColor;
}