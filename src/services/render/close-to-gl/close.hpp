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

	class PhongIlluminationModel {
	public:
		PhongIlluminationModel();
		vec3 apply(glm::vec3 position, glm::vec3 normal);
	private:
		float ambientStrength;
		float diffuseStrength;
		float specularStrength;
		vec3 light;
		vec3 camera;
		vec3 color;
		vec3 lightColor;
		vec3 getReflection(vec3 I, vec3 normal);
		vec3 getLightDirection(vec3 position);
		vec3 getAmbientLight();
		vec3 getDiffuseLight(vec3 normal, vec3 direction);
		vec3 getSpecularLight(vec3 normal, vec3 position, vec3 direction);
	};

	class VertexShader {
	public:
		VertexShader(VertexPayload* buffer);
		size_t apply(VertexData* vertices, size_t size);
	private:
		Camera* camera;
		Config* config;
		ProjectionFromConfig* projectionProvider;
		VertexPayload* buffer;
		glm::mat4 getMV();
	};

	class CullingJob {
	public:
		CullingJob(VertexPayload* buffer);
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
		glm::vec4 transform(size_t width, size_t height, glm::vec4 vertex);
		Config* config;
		VertexPayload* buffer;
	};

	class CloseToGLPipeline {
	public:
		std::unique_ptr<vector<unsigned char>> apply(data::VertexData*, size_t size);
		CloseToGLPipeline();
	private:
		VertexShader* toHomogeneousClipSpace;
		CullingJob* culling;
		PerspectiveAndViewport* normalization;
		RasterJob* raster;
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
