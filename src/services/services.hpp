#pragma once

#include "../data/data.hpp"
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <string>
#include <stdexcept>
#include <memory>

class ModelToVertex {
public:
	std::vector<data::VertexData>* getVertexDataFromDataModel(data::Model* model);
	data::VertexDataRange getRange(std::vector<data::VertexData>* vertices);
};

class ModelFactory {
private:
	FILE* open(std::string path);

	std::string* fetchName(FILE*);
	std::vector<data::Material*>* fetchMaterials(FILE*);
	data::Material* fetchMaterial(FILE*);
	std::vector<data::Triangle*>* fetchTriangles(FILE*, int);
	data::Triangle* fetchTriangle(FILE*);
	std::vector<data::Vertex*>* fetchVertices(FILE*);
	data::Vertex* fetchVertex(FILE*);

	void colorPreprocessing(data::Model* model);
	int getTriangleCount(FILE*);
	void skipLine(FILE*);
public:
	data::Model* get(std::string);
};

class Config {
private:
	static Config* instance;
	Config();
	float color[4] = { 0.0f, 0.90f, 1.0f, 1.0f };
	bool move = false;
	bool mouseStatus = false;
	int xfov = 90;
	int yfov = 90;
	int zNear = 1;
	int zFar = 1000;
	bool isCW = true;
	float sensibility = 15.0f;
	float mouseSensibility = 15.0f;
	int windowWidth = 0;
	int windowHeight = 0;
	int renderMode = 0;
	bool useOpenGL = true;
public:
	static Config* getInstance();
	float* getColor();
	bool* getMove();
	int* getXFOV();
	int* getYFOV();
	int* getZNear();
	int* getZFar();
	bool* getCW();
	float* getSensibility();
	float* getMouseSensibility();
	int* getWindowWidth();
	int* getWindowHeight();
	bool* getMouseStatus();
	int* getRenderMode();
	bool* getOpenGLUse();
	void reset();
};


class ProjectionFromConfig {
private:
	Config* config;
public:
	glm::mat4 get();
	ProjectionFromConfig();
};