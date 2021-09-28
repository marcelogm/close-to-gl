#include "close.hpp"
#include <glm/gtx/normal.hpp>

using namespace close;

#define TRIANGLE_VERTICES 3

std::vector<data::VertexPayload> CullingJob::apply(std::vector<data::VertexPayload>* vertices) {
	std::vector<data::VertexPayload> clipped(0);
	const size_t size = vertices->size() / TRIANGLE_VERTICES;
	for (size_t i = 0; i < size; i++) {
		const size_t start = i * TRIANGLE_VERTICES;
		if (!shouldDiscard(vertices, start)) {
			clipped.push_back(vertices->at(start));
			clipped.push_back(vertices->at(start + 1));
			clipped.push_back(vertices->at(start + 2));
		}
	}
	return clipped;
}

bool CullingJob::shouldDiscard(std::vector<data::VertexPayload>* primitive, size_t start) {
	return this->backfaceCullingTest(primitive, start) ||
		this->atLeastOneVerticeOutsideFrustum(primitive, start);
}

bool CullingJob::atLeastOneVerticeOutsideFrustum(std::vector<data::VertexPayload>* primitive, size_t start) {
	return !this->isInsideFrustum(&primitive->at(start).position) ||
		!this->isInsideFrustum(&primitive->at(start + 1).position) ||
		!this->isInsideFrustum(&primitive->at(start + 2).position);
}

bool CullingJob::isInsideFrustum(glm::vec4* point) {
	const auto x = point->x;
	const auto y = point->y;
	const auto w = point->w;
	const auto z = point->z;
	
	return ((-w <= x) && (x <= w)) &&
		((-w <= y) && (y <= w)) &&
		((-w <= z) && (z <= w)) &&
		(0 < w);
}

bool CullingJob::backfaceCullingTest(std::vector<data::VertexPayload>* primitive, size_t start) {
	const auto p1 = glm::vec3(primitive->at(start).position);
	const auto p2 = glm::vec3(primitive->at(start + 1).position);
	const auto p3 = glm::vec3(primitive->at(start + 2).position);
	const auto normal = glm::triangleNormal(p1, p2, p3);
	const auto n = glm::dot(normal, p1);

	if (!*Config::getInstance()->getCW()) {
		return n < 0.0f;
	}
	return n > 0.0f;
}

