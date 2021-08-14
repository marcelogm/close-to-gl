#include "data.hpp"

using namespace data;

Triangle::Triangle(const Triangle& triangles) {
	vertices = new std::vector<Vertex*>(triangles.vertices->size());
	for (int i = 0; i < triangles.vertices->size(); i++) {
		vertices->at(i) = new Vertex(*triangles.vertices->at(i));
	}
	faceNormal = new glm::vec3(*triangles.faceNormal);
};

Triangle::Triangle(std::vector<Vertex*>* vertices, glm::vec3* normal) {
	this->vertices = vertices;
	this->faceNormal = normal;
};

std::vector<Vertex*>* Triangle::getVertices() {
	return vertices;
}

glm::vec3* Triangle::getFaceNormal() {
	return faceNormal;
}

Triangle::~Triangle() {
	for (auto v : *vertices) { delete v; }
	delete vertices;
	delete faceNormal;
}