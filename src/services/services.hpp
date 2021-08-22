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

class Config {
private:
	static Config* instance;
	Config();
	float color[4] = { 1.0f, 0.1f, 0.1f, 1.0f };
	bool move = false;
	int fov = 45;
	int zNear = 1;
	int zFar = 200;
	bool isCW = true;
	float sensibility = 15.0f;
public:
	static Config* getInstance();
	float* getColor();
	bool* getMove();
	int* getFOV();
	int* getZNear();
	int* getZFar();
	bool* getCW();
	float* getSensibility();
};