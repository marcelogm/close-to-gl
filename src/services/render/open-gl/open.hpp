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

	class OpenGLRenderer : public renderer::Renderer {
	public:
		void init(data::Model*);
		void display();
		bool test();
		OpenGLRenderer();
	private:
		data::VertexData* vertices;
		data::VertexDataRange range;
		GLuint VAOs[NumVAOs];
		GLuint buffers[NumBuffers];
		unsigned int verticesCount;
		long modelSpace;
		long viewSpace;
		long projectionSpace;
		long normalTransform;
		GLuint program;
		ModelToVertex* converter;
		Config* config;
		Camera* camera;
		renderer::OpenGLDrawProcessor* drawer;
		renderer::BackgroundProcessor* background;
		renderer::CameraResetProcessor* reset;
		renderer::LightProcessor* light;
		ProjectionFromConfig* projectionProvider;
		std::vector<ShaderInfo> getShaders();
	};
}
