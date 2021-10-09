#pragma once

#include "../data/data.hpp"
#include <vgl.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <string>
#include <stdexcept>
#include <memory>
#include <stb_image.h>

#define RENDER_MODE_TRIANGLE 0
#define RENDER_MODE_DOT 1
#define RENDER_MODE_FRAME 2

#define LIGHT_NO_SHADING 1
#define LIGHT_GOURAUD_AD 2
#define LIGHT_GOURAUD_ADS 3
#define LIGHT_PHONG_SHADING 4

#define NEAREST_NEIGHBOR_RESAMPLING 1
#define BILINEAR_RESAMPLING 2
#define MIP_PAPPING_RESAMPLING 3

using std::string;
using std::vector;
using data::Model;
using data::Material;
using data::Triangle;
using data::Vertex;
using data::VertexData;
using data::VertexDataRange;

class ModelToVertex {
public:
	VertexData* getVertexDataFromDataModel(data::Model* model);
	VertexDataRange getRange(VertexData* vertices, size_t size);
};

class ModelFactory {
private:
	FILE* open(string path);

	string* fetchName(FILE*);
	vector<Material*>* fetchMaterials(FILE*);
	Material* fetchMaterial(FILE*);
	vector<Triangle*>* fetchTriangles(FILE*, int, bool);
	Triangle* fetchTriangle(FILE*, bool);
	Vertex* fetchVertex(FILE*, bool);

	bool hasTexture(FILE* file);
	void colorPreprocessing(data::Model* model);
	int getTriangleCount(FILE*);
	void skipLine(FILE*);
public:
	data::Model* get(string);
};

// TODO: essa classe está crescendo de mais, não alimente esse monstro, refatore.
class Config {
private:
	static Config* instance;
	Config();
	float color[4] = { 0.0f, 0.90f, 1.0f, 1.0f };
	float lightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float ambientStrength = 0.1f;
	float diffuseStrength = 0.8f;
	float specularStrength = 0.0f;
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
	bool modelCW = true;
	bool useTexture = false;
	int filtering = 1;
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
	bool* getCWModel();
	bool* getTextureUse();
	int* getShading();
	int* getFiltering();
	glm::vec3* getLightPosition();
	GLuint* getCloseToGLProgramId();
	GLuint* getCloseToGLTextureId();
	void reset();
};

class TextureProvider {
public:
	data::Texture get();
	TextureProvider();
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