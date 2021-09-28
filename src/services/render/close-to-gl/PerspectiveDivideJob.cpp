#include "close.hpp"

using namespace close;

std::vector<data::VertexPayload> PerspectiveDivideJob::apply(std::vector<data::VertexPayload>* vertices) {
	std::vector<data::VertexPayload> transformed(vertices->size());
	for (size_t i = 0; i < vertices->size(); i++) {
		const auto vertex = vertices->at(i);
		transformed[i] = {
			this->transform(vertex.position),
			vertex.normal,
			vertex.color
		};
	}
	return transformed;
};

glm::vec4 PerspectiveDivideJob::transform(glm::vec4 vertex) {
	return glm::vec4(
		vertex.x / vertex.w, 
		vertex.y / vertex.w, 
		vertex.z / vertex.w,
		1.0f / vertex.w
	);
}

