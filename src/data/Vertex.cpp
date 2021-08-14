#include "data.hpp"

using namespace data;

Vertex::Vertex(const Vertex& vertex) {
	position = new glm::vec3(*vertex.position);
	normal = new glm::vec3(*vertex.normal);
	colorIndex = vertex.colorIndex;
	color = new RGBColor(*vertex.color);
};

Vertex::Vertex(glm::vec3* position, glm::vec3* normal, int colorIndex) {
	this->position = position;
	this->normal = normal;
	this->colorIndex = colorIndex;
	this->color = new RGBColor({ 0, 0, 0 });
};

void Vertex::setColor(RGBColor* color) {
	delete this->color;
	this->color = color;
}

glm::vec3* Vertex::getPosition() {
	return position;
}

glm::vec3* Vertex::getNormal() {
	return normal;
}

int Vertex::getColorIndex() {
	return colorIndex;
}

RGBColor* Vertex::getColor() {
	return color;
}

Vertex::~Vertex() {
	delete position;
	delete normal;
	delete color;
}