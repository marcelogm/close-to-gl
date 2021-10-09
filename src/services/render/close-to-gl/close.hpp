#include "../render.hpp"
#include "raster/raster.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::unique_ptr;
using std::vector;
using data::VertexPayload;
using data::VertexData;
using glm::vec3;
using glm::vec4;
using glm::mat4;

namespace close {

	enum VAOIDs {
		Triangles = 0,
		NumVAOs = 1
	};

	enum BufferIDs {
		VertexBuffer = 0,
		NumBuffers = 1
	};

	enum AttribIDs {
		vPosition = 0,
		aTexCoord = 1
	};

	class Shader {
	public:
		virtual vec4 apply(vec4 position, vec4 normal) = 0;
		virtual bool test() = 0;
	};

	class ColorShader : public Shader {
	public:
		ColorShader();
		bool test();
		vec4 apply(glm::vec4 position, glm::vec4 normal);
	private:
		Config* config;
	};

	class PhongIlluminationModel : public Shader {
	public:
		PhongIlluminationModel();
		bool test();
		vec4 apply(glm::vec4 position, glm::vec4 normal);
	private:
		Config* config;
		float* ambientStrength;
		float* diffuseStrength;
		float* specularStrength;
		vec3* light;
		vec3* camera;
		vec3 getLightColor();
		vec3 getObjectColor();
		vec3 getReflection(vec3* I, vec3* normal);
		vec3 getLightDirection(vec3* position);
		vec3 getAmbientLight(vec3* color);
		vec3 getDiffuseLight(vec3* normal, vec3* direction, vec3* color);
		vec3 getSpecularLight(vec3* normal, vec3* position, vec3* direction, vec3* color);
	};

	class VertexShader {
	public:
		VertexShader(VertexPayload* buffer);
		size_t apply(VertexData* vertices, size_t size);
	private:
		Camera* camera;
		Config* config;
		renderer::ProjectionFromConfig* projectionProvider;
		VertexPayload* buffer;
		vector<Shader*>* shaders;
		glm::mat4 getMV();
		Shader* getShader();
	};

	class FaceCulling {
	public:
		FaceCulling(VertexPayload* buffer);
		size_t apply(size_t verticeCount);
	private:
		bool shouldDiscard(size_t);
		bool atLeastOneVerticeOutsideFrustum(size_t);
		bool backfaceCullingTest(size_t);
		bool isInsideFrustum(glm::vec4* point);
		VertexPayload* buffer;
	};

	class PerspectiveAndViewport {
	public:
		PerspectiveAndViewport(VertexPayload* buffer);
		size_t apply(size_t count);
	private:
		VertexPayload transform(size_t width, size_t height, VertexPayload* vertex);
		Config* config;
		VertexPayload* buffer;
	};

	class CloseToGLPipeline {
	public:
		vector<unsigned char> apply(data::VertexData*, size_t size);
		CloseToGLPipeline();
	private:
		VertexShader* vertexShader;
		FaceCulling* culling;
		PerspectiveAndViewport* normalization;
		Rasterizer* raster;
		VertexPayload* buffer;
	};

	class CloseToGLRenderer : public renderer::Renderer {
	public:
		void init(data::Model*);
		void display();
		bool test();
		CloseToGLRenderer();
	private:
		VertexData* vertices;
		size_t size;
		data::VertexDataRange range;
		GLuint VAOs[NumVAOs];
		GLuint buffers[NumBuffers];
		GLuint program;
		GLuint texture;
		unsigned char* data;
		Config* config;
		long customColor;
		unsigned int verticesCount;
		renderer::BackgroundProcessor* background;
		renderer::CameraResetProcessor* reset;
		CloseToGLPipeline* pipeline;
		vector<ShaderInfo> getShaders();
		// POSITION, MAPPING
		GLfloat panelVertices[24] = { -1.0f, -1.0f, 0.0f, 0.0f,
									   1.0f, -1.0f, 1.0f, 0.0f,
			                           1.0f,  1.0f, 1.0f, 1.0f,
								       1.0f,  1.0f, 1.0f, 1.0f,
			                          -1.0f,  1.0f, 0.0f, 1.0f,
			                          -1.0f, -1.0f, 0.0f, 0.0f };
	};
}
