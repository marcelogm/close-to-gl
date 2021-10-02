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

	class LightProcessor {
	public:
		void setup(GLuint program);
		void process();
		LightProcessor();
	private:
		GLuint customColor;
		GLuint lightPosition;
		GLuint lightColor;
		GLuint ambientStrength;
		GLuint diffuseStrength;
		GLuint specularStrength;
		GLuint cameraPosition;
		GLuint gouraudADSubroutine;
		GLuint gouraudADSSubroutine;
		GLuint noVertexShading;
		GLuint noFragmentShading;
		GLuint phongShading;
		Camera* camera;
		Config* config;
	};

	class OpenGLDrawProcessor {
	public:
		void process(size_t);
		OpenGLDrawProcessor();
	private:
		Config* config;
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
		OpenGLDrawProcessor* drawer;
		renderer::BackgroundProcessor* background;
		renderer::CameraResetProcessor* reset;
		LightProcessor* light;
		renderer::ProjectionFromConfig* projectionProvider;
		std::vector<ShaderInfo> getShaders();
	};
}
