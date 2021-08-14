#include "data.hpp"

using namespace data;

Model::Model(const Model& model) {
	name = new std::string(*model.name);
	triangles = new std::vector<Triangle*>(model.triangles->size());
	for (int i = 0; i < model.triangles->size(); i++) {
		triangles->at(i) = new Triangle(*model.triangles->at(i));
	}
	materials = new std::vector<Material*>(model.materials->size());
	for (int i = 0; i < model.materials->size(); i++) {
		materials->at(i) = new Material(*model.materials->at(i));
	}
}

Model::Model(std::string* name, std::vector<Triangle*>* triangles, std::vector<Material*>* materials) {
	this->name = name;
	this->triangles = triangles;
	this->materials = materials;
};

std::string* Model::getName() {
	return name;
}

std::vector<Triangle*>* Model::getTriangles() {
	return triangles;
}

std::vector<Material*>* Model::getMaterials() {
	return materials;
}

Model::~Model() {
	for (auto t : *triangles) { delete t; }
	delete triangles;
	for (auto m : *materials) { delete m; }
	delete materials;
	delete name;
}