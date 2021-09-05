#include "close.hpp"

using namespace close;

std::vector<glm::vec3> PerspectiveDivideJob::apply(std::vector<glm::vec4> vertices) {
	std::vector<glm::vec3> positions(0);
	for (size_t i = 0; i < vertices.size(); i++) {
		auto w = vertices[i].w;
		if ((-w <= vertices[i].x <= w) ||
			(-w <= vertices[i].y <= w) ||
			(-w <= vertices[i].z <= w)) {
			positions.push_back(glm::vec3(
				vertices[i].x / w,
				vertices[i].y / w,
				vertices[i].z / w
			));
		}
		
	}
	return positions;
};