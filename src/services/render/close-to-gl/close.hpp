#include "../render.hpp"
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
		vNormalVertex = 1
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

	class VertexShaderJob : public Job<std::vector<data::VertexData>*, std::vector<glm::vec4>> {
	public:
		std::vector<glm::vec4> apply(std::vector<data::VertexData>*);
		VertexShaderJob();
	private:
		Camera* camera;
		ProjectionFromConfig* projectionProvider;
		glm::mat4 getMVP();
		glm::vec4 toHomogeneous(data::VertexData);
	};

	class ClippingJob : public Job<std::vector<glm::vec4>, std::vector<glm::vec4>> {
	public:
		std::vector<glm::vec4> apply(std::vector<glm::vec4>);
	};

	class PerspectiveDivideJob : public Job<std::vector<glm::vec4>, std::vector<glm::vec3>> {
	public:
		std::vector<glm::vec3> apply(std::vector<glm::vec4>);
	};

	class ViewportTransformJob : public Job<std::vector<glm::vec3>, std::vector<data::VertexData2D>> {
	public:
		std::vector<data::VertexData2D> apply(std::vector<glm::vec3>);
	};

	class CloseToGLPipeline : public Pipeline<std::vector<data::VertexData>*, std::unique_ptr<std::vector<data::VertexData2D>>> {
	public:
		std::unique_ptr<std::vector<data::VertexData2D>> apply(std::vector<data::VertexData>*);
		CloseToGLPipeline();
	private:
		VertexShaderJob* toHomogeneousClipSpace;
		ClippingJob* clipping;
		PerspectiveDivideJob* normalization;
		ViewportTransformJob* toViewport;
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
		Config* config;
		unsigned int verticesCount;
		CloseToGLPipeline* pipeline;
	};
}
