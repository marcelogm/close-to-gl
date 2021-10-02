#include "render.hpp"

using namespace renderer;

void LightProcessor::process() {
	const float* objectColor = config->getColor();
	const float* lightColorValue = config->getLightColor();

	const glm::vec3* lightPositionValue = config->getLightPosition();
	const glm::vec3* cameraPositionValue = camera->getPosition();

	glUniform1f(ambientStrength, *config->getAmbientStrength()); 
	glUniform1f(diffuseStrength, *config->getDiffuseStrength());
	glUniform1f(specularStrength, *config->getSpecularStrength());
	glUniform3f(lightPosition, lightPositionValue->x, lightPositionValue->y, lightPositionValue->z);
	glUniform3f(cameraPosition, cameraPositionValue->x, cameraPositionValue->y, cameraPositionValue->z);
	glUniform4f(customColor, objectColor[0], objectColor[1], objectColor[2], objectColor[3]);
	glUniform3f(lightColor, lightColorValue[0], lightColorValue[1], lightColorValue[2]);

	switch (*config->getShading()) {
	case 1:
		glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &noVertexShading);
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &noFragmentShading);
		break;
	case 2:
		glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &gouraudADSubroutine);
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &noFragmentShading);
		break;
	case 3:
		glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &gouraudADSSubroutine);
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &noFragmentShading);
		break;
	case 4:
		glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &noVertexShading);
		glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &phongShading);
		break;
	}
}

void LightProcessor::setup(GLuint program) {
	this->customColor = glGetUniformLocation(program, "customColor");
	this->lightPosition = glGetUniformLocation(program, "lightPosition");
	this->lightColor = glGetUniformLocation(program, "lightColor");

	this->ambientStrength = glGetUniformLocation(program, "ambientStrength");
	this->diffuseStrength = glGetUniformLocation(program, "diffuseStrength");
	this->specularStrength = glGetUniformLocation(program, "specularStrength");

	this->noVertexShading = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "noShading");
	this->gouraudADSubroutine = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "gouraudShadingAD");
	this->gouraudADSSubroutine = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "gouraudShadingADS");

	this->noFragmentShading = glGetSubroutineIndex(program, GL_FRAGMENT_SHADER, "noShading");
	this->phongShading = glGetSubroutineIndex(program, GL_FRAGMENT_SHADER, "phongShading");
}

LightProcessor::LightProcessor() {
	this->camera = Camera::getInstance();
	this->config = Config::getInstance();
}