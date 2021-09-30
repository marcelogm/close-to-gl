#include "close.hpp"

using namespace close;

PerspectiveDivideJob::PerspectiveDivideJob(vector<VertexPayload>* buffer) {
	this->buffer = buffer;
}

size_t PerspectiveDivideJob::apply(size_t count) {
	for (size_t i = 0; i < count; i++) {
		const auto vertex = buffer->at(i);
		buffer->at(i) = {
			this->transform(vertex.position),
			vertex.normal,
			vertex.color
		};
	}
	return count;
};

glm::vec4 PerspectiveDivideJob::transform(glm::vec4 vertex) {
	return glm::vec4(
		vertex.x / vertex.w, 
		vertex.y / vertex.w, 
		vertex.z / vertex.w,
		1.0f / vertex.w
	);
}

