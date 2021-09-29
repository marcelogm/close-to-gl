#include "../render.hpp"
#include "raster/raster.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	template<typename I, typename O>
	class Job {
	public:
		virtual O apply(I) = 0;
	};

	template<typename I, typename O>
	class Pipeline {
	public:
		virtual O apply(I) = 0;
	};

	class PhongIlluminationModel {
	public:
		PhongIlluminationModel();
		glm::vec4 apply(glm::vec4 position, glm::vec4 normal);
	private:

		float ambientStrength;
		float diffuseStrength;
		float specularStrength;

		glm::vec4 light;
		glm::vec4 camera;

		glm::vec4 color;
		glm::vec4 lightColor;
		glm::vec4 getReflection(glm::vec4 I, glm::vec4 normal);
		glm::vec4 getLightDirection(glm::vec4 position);
		glm::vec4 getAmbientLight();
		glm::vec4 getDiffuseLight(glm::vec4 normal, glm::vec4 direction);
		glm::vec4 getSpecularLight(glm::vec4 normal, glm::vec4 position, glm::vec4 direction);
	};

	class VertexShaderJob : public Job<std::vector<data::VertexData>*, std::vector<data::VertexPayload>> {
	public:
		std::vector<data::VertexPayload> apply(std::vector<data::VertexData>*);
		VertexShaderJob();
	private:
		Camera* camera;
		Config* config;
		ProjectionFromConfig* projectionProvider;
		PhongIlluminationModel* illumination;
		glm::mat4 getMVP();
		glm::vec4 toHomogeneous(data::VertexData* vertex);

	};

	class CullingJob : public Job<std::vector<data::VertexPayload>*, std::vector<data::VertexPayload>> {
	public:
		std::vector<data::VertexPayload> apply(std::vector<data::VertexPayload>*);
	private:
		bool shouldDiscard(std::vector<data::VertexPayload>* primitive, size_t start);
		bool atLeastOneVerticeOutsideFrustum(std::vector<data::VertexPayload>* primitive, size_t start);
		bool backfaceCullingTest(std::vector<data::VertexPayload>* primitive, size_t start);
		bool isInsideFrustum(glm::vec4* point);
	};

	class PerspectiveDivideJob : public Job<std::vector<data::VertexPayload>*, std::vector<data::VertexPayload>> {
	public:
		std::vector<data::VertexPayload> apply(std::vector<data::VertexPayload>*);
		glm::vec4 transform(glm::vec4 vertex);
	};

	class ViewportTransformationJob : public Job<std::vector<data::VertexPayload>*, std::vector<data::VertexPayload>> {
	public:
		std::vector<data::VertexPayload> apply(std::vector<data::VertexPayload>*);
		ViewportTransformationJob();
	private:
		Config* config;
	};


	class CloseToGLPipeline : public Pipeline<std::vector<data::VertexData>*, std::unique_ptr<std::vector<unsigned char>>> {
	public:
		std::unique_ptr<std::vector<unsigned char>> apply(std::vector<data::VertexData>*);
		CloseToGLPipeline();
	private:
		VertexShaderJob* toHomogeneousClipSpace;
		CullingJob* culling;
		PerspectiveDivideJob* normalization;
		ViewportTransformationJob* viewport;
		RasterJob* raster;
	};

	class CloseToGLRenderer : public renderer::Renderer {
	public:
		void init(data::Model*);
		void display();
		bool test();
		CloseToGLRenderer();
	private:
		std::vector<data::VertexData>* vertices;
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
		std::vector<ShaderInfo> getShaders();
		// POSITION, MAPPING
		GLfloat panelVertices[24] = { -1.0f, -1.0f, 0.0f, 0.0f,
									   1.0f, -1.0f, 1.0f, 0.0f,
			                           1.0f,  1.0f, 1.0f, 1.0f,
								       1.0f,  1.0f, 1.0f, 1.0f,
			                          -1.0f,  1.0f, 0.0f, 1.0f,
			                          -1.0f, -1.0f, 0.0f, 0.0f };
	};
}
