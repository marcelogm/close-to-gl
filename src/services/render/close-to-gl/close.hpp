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

	class VertexShaderJob : public Job<std::vector<glm::vec4>, std::vector<data::VertexData>*> {
	public:
		std::vector<glm::vec4> apply(std::vector<data::VertexData>*);
	};

	class ClippingJob : public Job<std::vector<glm::vec4>, std::vector<glm::vec4>> {
	public:
		std::vector<glm::vec4> apply(std::vector<glm::vec4>);
	};

	class PerspectiveDivideJob : public Job<std::vector<glm::vec4>, std::vector<glm::vec3>> {
	public:
		std::vector<glm::vec3> apply(std::vector<glm::vec4>);
	};

	class ViewportTransformJob : public Job<std::vector<glm::vec4>, std::vector<glm::vec2>> {
	public:
		std::vector<data::VertexData2D> apply(std::vector<glm::vec3>);
	};

	class CloseToGLPipeline : public Pipeline<std::unique_ptr<std::vector<glm::vec2>>, std::vector<data::VertexData*>> {
	public:
		std::unique_ptr<std::vector<data::VertexData2D>> apply(std::vector<data::VertexData>*);
		CloseToGLPipeline();
	private:
		std::unique_ptr<VertexShaderJob> toHomogeneousClipSpace;
		std::unique_ptr<ClippingJob> clipping;
		std::unique_ptr<PerspectiveDivideJob> normalization;
		std::unique_ptr<ViewportTransformJob> toViewport;
	};

	class ModelToVertex {
	public:
		std::vector<data::VertexData>* getVertexDataFromDataModel(data::Model* model);
		data::VertexDataRange getRange(std::vector<data::VertexData>* vertices);
	};

	class CloseToGLRenderer : public renderer::Renderer {
	public:
		void init(data::Model*);
		void display();
		bool test();
		CloseToGLRenderer();
	};
}
