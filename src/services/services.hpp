#pragma once

#include "../data/data.hpp"
#include <string>
#include <stdexcept>
#include <memory>

using namespace std;

class ModelFactory {
private:
	FILE* open(string path);

	string* fetchName(FILE*);
	vector<data::Material*>* fetchMaterials(FILE*);
	data::Material* fetchMaterial(FILE*);
	vector<data::Triangle*>* fetchTriangles(FILE*, int);
	data::Triangle* fetchTriangle(FILE*);
	vector<data::Vertex*>* fetchVertices(FILE*);
	data::Vertex* fetchVertex(FILE*);

	void colorPreprocessing(data::Model* model);
	int getTriangleCount(FILE*);
	void skipLine(FILE*);
public:
	data::Model* get(string);
};