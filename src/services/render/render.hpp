#include <vgl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <LoadShaders.h>
#include "../../data/data.hpp"
#include "../services.hpp"
#include "../camera/camera.hpp"

using namespace std;

enum VAOIDs {
	Triangles = 0,
	NumVAOs = 1
};

enum BufferIDs {
	VertexBuffer = 0,
	NormalBuffer = 1,
	NumBuffers = 2
};

enum AttribIDs {
	vPosition = 0,
	vNormalVertex = 1
};

struct VertexData {
	GLfloat position[3];
	GLfloat normal[3];
	GLubyte color[3];
};

struct VertexDataRange {
	glm::vec2 x;
	glm::vec2 y;
	glm::vec2 z;
};

class OpenGLRenderer {
public:
	void init(data::Model*);
	void display();
	vector<ShaderInfo> getShaders();
private:
	vector<VertexData>* vertices;
	VertexDataRange range;
	GLuint VAOs[NumVAOs];
	GLuint buffers[NumBuffers];
	unsigned int verticesCount;
	long modelSpace;
	long viewSpace;
	long projectionSpace;
	long customColor;

	vector<VertexData>* getVertexDataFromDataModel(data::Model* model);
	VertexDataRange getRange(vector<VertexData>* vertices);
};