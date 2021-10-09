#include "services.hpp"
#include <stb_image.h>

using namespace data;

Model* ModelFactory::get(std::string path) {
	char ch;
	const auto file = open(path);
	const auto name = fetchName(file);
	const int trianglesCount = getTriangleCount(file);
	const auto materials = fetchMaterials(file);
	const bool hasTexture = this->hasTexture(file);
	skipLine(file);
	auto triangles = fetchTriangles(file, trianglesCount, hasTexture);
	fclose(file);
	auto model = new Model(name, triangles, materials);
	colorPreprocessing(model);
	return model;
}

FILE* ModelFactory::open(std::string path) {
	FILE* fp = fopen(path.c_str(), "r");
	if (fp == NULL) {
		throw std::runtime_error("Could not open file");
	}
}

std::string* ModelFactory::fetchName(FILE* file) {
	std::string str(10, '\0');
	(void)fscanf(file, "Object name = %s\n", str.data());
	str.resize(strlen(str.data()));
	return new std::string(str);
}

int ModelFactory::getTriangleCount(FILE* file) {
	int triangles;
	(void)fscanf(file, "# triangles = %d\n", &triangles);
	return triangles;
}

void ModelFactory::skipLine(FILE* file) {
	(void)fscanf(file, "%*[^\n]\n");
}

vector<Material*>* ModelFactory::fetchMaterials(FILE* file) {
	int count;
	vector<Material*>* materials = new vector<Material*>();
	(void)fscanf(file, "Material count = %d\n", &count);
	for (int i = 0; i < count; i++) {
		materials->push_back(fetchMaterial(file));
	}
	return materials;
}

Material* ModelFactory::fetchMaterial(FILE* file) {
	vec3* ambient = new vec3();
	vec3* diffuse = new vec3();
	vec3* specular = new vec3();
	float shine;

	(void)fscanf(file, "ambient color %f %f %f\n", &(ambient->x), &(ambient->y), &(ambient->z));
	(void)fscanf(file, "diffuse color %f %f %f\n", &(diffuse->x), &(diffuse->y), &(diffuse->z));
	(void)fscanf(file, "specular color %f %f %f\n", &(specular->x), &(specular->y), &(specular->z));
	(void)fscanf(file, "material shine %f\n", &shine);

	return new Material(ambient, diffuse, specular, shine);
}

vector<Triangle*>* ModelFactory::fetchTriangles(FILE* file, int count, bool hasTexture) {
	vector<Triangle*>* triangles = new vector<Triangle*>();
	for (int i = 0; i < count; i++) {
		triangles->push_back(fetchTriangle(file, hasTexture));
	}
	return triangles;
}

Triangle* ModelFactory::fetchTriangle(FILE* file, bool hasTexture) {
	vector<Vertex*>* vertices = new vector<Vertex*>();
	vec3* normal = new vec3();

	for (int i = 0; i < 3; i++) {
		vertices->push_back(fetchVertex(file, hasTexture));
	}
	(void)fscanf(file, "face normal %f %f %f\n", &(normal->x), &(normal->y), &(normal->z));

	return new Triangle(vertices, normal);
}

Vertex* ModelFactory::fetchVertex(FILE* file, bool hasTexture) {
	vec3* position = new vec3();
	vec3* normal = new vec3();
	vec2* texture = nullptr;
	int colorIndex, i;

	// TODO: não tá bom, um lambda aqui seria legal
	if (hasTexture) {
		texture = new vec2();
		(void)fscanf(file, "v%d %f %f %f %f %f %f %d %f %f\n", &i,
			&(position->x), &(position->y), &(position->z),
			&(normal->x), &(normal->y), &(normal->z),
			&colorIndex, &(texture->x), &(texture->y));
	} else {
		(void)fscanf(file, "v%d %f %f %f %f %f %f %d\n", &i,
			&(position->x), &(position->y), &(position->z),
			&(normal->x), &(normal->y), &(normal->z),
			&colorIndex);
	}

	return new Vertex(position, normal, texture, colorIndex, hasTexture);
}

bool ModelFactory::hasTexture(FILE* file) {
	std::string str(10, '\0');
	(void)fscanf(file, "Texture = %s\n", str.data());
	return str.compare("YES") == 1;
}

void ModelFactory::colorPreprocessing(Model* model) {
	for (int i = 0; i < model->getTriangles()->size(); i++) {
		auto triangle = model->getTriangles()->at(i);
		for (int j = 0; j < triangle->getVertices()->size(); j++) {
			auto vertex = triangle->getVertices()->at(j);
			auto material = model->getMaterials()->at(vertex->getColorIndex());
			auto color = material->getDiffuseColor();
			vertex->setColor(new RGBColor({
					(unsigned char)((int) 255 * color->x),
					(unsigned char)((int) 255 * color->y),
					(unsigned char)((int) 255 * color->z)
			}));
		}
	}
}