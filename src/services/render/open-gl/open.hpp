#include "../render.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

namespace open {

	enum VAOIDs {
		Triangles = 0,
		NumVAOs = 1
	};

	enum BufferIDs {
		VertexBuffer = 0,
		NormalBuffer = 1,
		TextCoord = 2,
		NumBuffers = 3
	};

	enum AttribIDs {
		vPosition = 0,
		vNormalVertex = 1,
		aTextCoord = 2
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
		GLuint useTexture;
		Camera* camera;
		Config* config;
	};

	class FilteringProcessor {
	public:
		void process();
		FilteringProcessor();
	private:
		Config* config;
	};

	class OpenGLDrawProcessor {
	public:
		void process(size_t vertices);
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
		long texturaLocation;
		GLuint program;
		GLuint texture;
		ModelToVertex* converter;
		Config* config;
		Camera* camera;
		OpenGLDrawProcessor* drawer;
		renderer::BackgroundProcessor* background;
		renderer::CameraResetProcessor* reset;
		LightProcessor* light;
		FilteringProcessor* filter;
		renderer::ProjectionFromConfig* projectionProvider;
		std::vector<ShaderInfo> getShaders();
		data::Texture getTexture();
	};
}
