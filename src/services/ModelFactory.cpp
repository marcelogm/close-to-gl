#include "services.hpp"

using namespace std;

data::Model* ModelFactory::get(string path) {
	char ch;
	auto file = open(path);
	auto name = fetchName(file);
	int trianglesCount = getTriangleCount(file);
	auto materials = fetchMaterials(file);
	skipLine(file);
	auto triangles = fetchTriangles(file, trianglesCount);
	fclose(file);
	auto model = new data::Model(name, triangles, materials);
	colorPreprocessing(model);
	return model;
}

FILE* ModelFactory::open(string path) {
	FILE* fp = fopen(path.c_str(), "r");
	if (fp == NULL) {
		throw runtime_error("Could not open file");
	}
}

string* ModelFactory::fetchName(FILE* file) {
	string str(10, '\0');
	(void)fscanf(file, "Object name = %s\n", str.data());
	str.resize(strlen(str.data()));
	return new string(str);
}

int ModelFactory::getTriangleCount(FILE* file) {
	int triangles;
	(void)fscanf(file, "# triangles = %d\n", &triangles);
	return triangles;
}

void ModelFactory::skipLine(FILE* file) {
	(void)fscanf(file, "%*[^\n]\n");
}

vector<data::Material*>* ModelFactory::fetchMaterials(FILE* file) {
	int count;
	vector<data::Material*>* materials = new vector<data::Material*>();
	(void)fscanf(file, "Material count = %d\n", &count);
	for (int i = 0; i < count; i++) {
		materials->push_back(fetchMaterial(file));
	}
	return materials;
}

data::Material* ModelFactory::fetchMaterial(FILE* file) {
	glm::vec3* ambient = new glm::vec3();
	glm::vec3* diffuse = new glm::vec3();
	glm::vec3* specular = new glm::vec3();
	float shine;

	(void)fscanf(file, "ambient color %f %f %f\n", &(ambient->x), &(ambient->y), &(ambient->z));
	(void)fscanf(file, "diffuse color %f %f %f\n", &(diffuse->x), &(diffuse->y), &(diffuse->z));
	(void)fscanf(file, "specular color %f %f %f\n", &(specular->x), &(specular->y), &(specular->z));
	(void)fscanf(file, "material shine %f\n", &shine);

	return new data::Material(ambient, diffuse, specular, shine);
}

vector<data::Triangle*>* ModelFactory::fetchTriangles(FILE* file, int count) {
	vector<data::Triangle*>* triangles = new vector<data::Triangle*>();
	for (int i = 0; i < count; i++) {
		triangles->push_back(fetchTriangle(file));
	}
	return triangles;
}

data::Triangle* ModelFactory::fetchTriangle(FILE* file) {
	vector<data::Vertex*>* vertices = new vector<data::Vertex*>();
	glm::vec3* normal = new glm::vec3();

	for (int i = 0; i < 3; i++) {
		vertices->push_back(fetchVertex(file));
	}
	(void)fscanf(file, "face normal %f %f %f\n", &(normal->x), &(normal->y), &(normal->z));

	return new data::Triangle(vertices, normal);
}

data::Vertex* ModelFactory::fetchVertex(FILE* file) {
	glm::vec3* position = new glm::vec3();
	glm::vec3* normal = new glm::vec3();
	int colorIndex, i;

	(void)fscanf(file, "v%d %f %f %f %f %f %f %d\n", &i,
		&(position->x), &(position->y), &(position->z),
		&(normal->x), &(normal->y), &(normal->z),
		&colorIndex);

	return new data::Vertex(position, normal, colorIndex);
}

void ModelFactory::colorPreprocessing(data::Model* model) {
	for (int i = 0; i < model->getTriangles()->size(); i++) {
		auto triangle = model->getTriangles()->at(i);
		for (int j = 0; j < triangle->getVertices()->size(); j++) {
			auto vertex = triangle->getVertices()->at(j);
			auto material = model->getMaterials()->at(vertex->getColorIndex());
			auto color = material->getDiffuseColor();
			vertex->setColor(new data::RGBColor({
					(unsigned char)((int) 255 * color->x),
					(unsigned char)((int) 255 * color->y),
					(unsigned char)((int) 255 * color->z)
			}));
		}
	}
}