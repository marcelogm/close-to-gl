#include "close.hpp"
#include <glm/gtx/normal.hpp>

using namespace close;

#define TRIANGLE_VERTICES 3

std::vector<glm::vec4> ClippingJob::apply(std::vector<glm::vec4>* vertices) {
	std::vector<glm::vec4> clipped(0);
	const size_t size = vertices->size();
	for (size_t i = 0; i < size; i++) {
		const auto j = i % TRIANGLE_VERTICES;
		if (!this->isInsideClippingSpace(vertices->at(i).z, vertices->at(i).w)) {
			// reject triangle 
			i += 3 - j;
		} else if (j == 2) {
			const auto p0 = vertices->at(i - 2);
			const auto p1 = vertices->at(i - 1); 
			const auto p2 = vertices->at(i);
			if (this->backfaceCullingTest(p0, p1, p2)) {
				clipped.push_back(p0);
				clipped.push_back(p1);
				clipped.push_back(p2);
			}
		}	
	}
	return clipped;
}

bool ClippingJob::isInsideClippingSpace(float z, float w) {
	return (-w <= z && z <= w) || (w < 0);
}

bool ClippingJob::backfaceCullingTest(glm::vec4 p0, glm::vec4 p1, glm::vec4 p2) {
	const auto v0 = glm::vec3(p0);
	const auto v1 = glm::vec3(p1);
	const auto v2 = glm::vec3(p2);
	const auto normal = glm::triangleNormal(v0, v1, v2);
	const auto n = glm::dot(normal, v0);
	
	if (*Config::getInstance()->getCW()) {
		return n < 0.0f;
	}
	return n > 0.0f;
}