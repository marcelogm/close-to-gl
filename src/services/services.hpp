#pragma once

#include "../data/data.hpp"
#include <vgl.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <string>
#include <stdexcept>
#include <memory>

#define RENDER_MODE_TRIANGLE 0
#define RENDER_MODE_DOT 1
#define RENDER_MODE_FRAME 2

#define LIGHT_NO_SHADING 1
#define LIGHT_GOURAUD_AD 2
#define LIGHT_GOURAUD_ADS 3
#define LIGHT_PHONG_SHADING 4


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
	float lightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float ambientStrength = 0.1f;
	float diffuseStrength = 0.8f;
	float specularStrength = 0.6f;
	bool move = false;
	bool mouseStatus = false;
	int xfov = 45;
	int yfov = 45;
	int zNear = 1;
	int zFar = 5000;
	bool isCW = true;
	float sensibility = 15.0f;
	float mouseSensibility = 15.0f;
	int windowWidth = 0;
	int windowHeight = 0;
	int renderMode = 0;
	bool useOpenGL = true;
	int shading = 1;
	GLuint texture;
	GLuint program;
	glm::vec3 lightPosition = glm::vec3(0.0f, 0.3f, 0.0f);
public:
	static Config* getInstance();
	float* getColor();
	float* getLightColor();
	float* getAmbientStrength();
	float* getDiffuseStrength();
	float* getSpecularStrength();
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
	int* getShading();
	glm::vec3* getLightPosition();
	GLuint* getCloseToGLProgramId();
	GLuint* getCloseToGLTextureId();
	void reset();
};


class ProjectionFromConfig {
private:
	Config* config;
public:
	glm::mat4 get();
	ProjectionFromConfig();
};

class Debug {
private:
	static Debug* instance;
	Debug();

	double framerate;
	double frametime;

	double lastFrameTime = 0.0;
	double currentFrameTime = 0.0;
	double timeFrameDiff = 0.0;
	size_t frameCounter = 0;
public:
	static Debug* getInstance();
	void countFrame();
	double getFramerate();
	double getFrametime();
};