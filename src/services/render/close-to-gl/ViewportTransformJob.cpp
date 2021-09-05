#include "close.hpp"

using namespace close;

std::vector<data::VertexData2D> ViewportTransformJob::apply(std::vector<glm::vec3> vertices) {
	std::vector<data::VertexData2D> positions(vertices.size());
	for (size_t i = 0; i < vertices.size(); i++) {
		auto point = glm::vec4(
			vertices[i].x,
			vertices[i].y,
			vertices[i].z,
			1.0f
		);
		positions[i] = { { point.x, point.y }, {255, 255, 255} };
	}
	return positions;
};