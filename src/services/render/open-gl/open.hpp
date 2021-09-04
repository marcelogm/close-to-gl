#include "../render.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace open {

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
		float position[3];
		float normal[3];
		unsigned char color[3];
	};

	struct VertexDataRange {
		glm::vec2 x;
		glm::vec2 y;
		glm::vec2 z;
	};

	class ModelToVertex {
	public:
		std::vector<VertexData>* getVertexDataFromDataModel(data::Model* model);
		VertexDataRange getRange(std::vector<VertexData>* vertices);
	};

	class OpenGLRenderer : public renderer::Renderer {
	public:
		void init(data::Model*);
		void display();
		bool test();
		OpenGLRenderer();
	private:
		std::vector<VertexData>* vertices;
		VertexDataRange range;
		GLuint VAOs[NumVAOs];
		GLuint buffers[NumBuffers];
		unsigned int verticesCount;
		long modelSpace;
		long viewSpace;
		long projectionSpace;
		long customColor;
		GLuint program;
		ModelToVertex* converter;
		Config* config;
		std::vector<ShaderInfo> getShaders();
	};
}
