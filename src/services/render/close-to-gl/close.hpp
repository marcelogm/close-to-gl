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

	struct VertexData2D {
		float position[2];
		unsigned char color[3];
	};

	struct VertexDataRange {
		glm::vec2 x;
		glm::vec2 y;
		glm::vec2 z;
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

	class VertexShaderJob : public Job<std::vector<glm::vec4>, std::vector<VertexData>*> {
	public:
		std::vector<glm::vec4> apply(std::vector<VertexData>*);
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
		std::vector<VertexData2D> apply(std::vector<glm::vec3>);
	};

	class CloseToGLPipeline : public Pipeline<std::unique_ptr<std::vector<glm::vec2>>, std::vector<VertexData*>> {
	public:
		std::unique_ptr<std::vector<VertexData2D>> apply(std::vector<VertexData>*);
		CloseToGLPipeline();
	private:
		std::unique_ptr<VertexShaderJob> toHomogeneousClipSpace;
		std::unique_ptr<ClippingJob> clipping;
		std::unique_ptr<PerspectiveDivideJob> normalization;
		std::unique_ptr<ViewportTransformJob> toViewport;
	};

	class ModelToVertex {
	public:
		std::vector<VertexData>* getVertexDataFromDataModel(data::Model* model);
		VertexDataRange getRange(std::vector<VertexData>* vertices);
	};

	class CloseToGLRenderer : public renderer::Renderer {
	public:
		void init(data::Model*);
		void display();
		bool test();
		CloseToGLRenderer();
	};
}
