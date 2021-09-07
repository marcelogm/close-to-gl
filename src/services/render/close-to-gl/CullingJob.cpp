#include "close.hpp"
#include <glm/gtx/normal.hpp>

using namespace close;

#define TRIANGLE_VERTICES 3

std::vector<glm::vec4> CullingJob::apply(std::vector<glm::vec4>* vertices) {
	std::vector<glm::vec4> clipped(0);
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

bool CullingJob::shouldDiscard(std::vector<glm::vec4>* primitive, size_t start) {
	return this->backfaceCullingTest(primitive, start) ||
		this->atLeastOneVerticeOutsideFrustumAtZ(primitive, start) || 
		this->allVerticesOutsideFrustumAtXAndY(primitive, start);
}

bool CullingJob::allVerticesOutsideFrustumAtXAndY(std::vector<glm::vec4>* primitive, size_t start) {
	return !this->isXYInsideFrustum(&primitive->at(start)) &&
		!this->isXYInsideFrustum(&primitive->at(start + 1)) &&
		!this->isXYInsideFrustum(&primitive->at(start + 2));
}

bool CullingJob::atLeastOneVerticeOutsideFrustumAtZ(std::vector<glm::vec4>* primitive, size_t start) {
	return !this->isZInsideFrustum(&primitive->at(start)) ||
		!this->isZInsideFrustum(&primitive->at(start + 1)) ||
		!this->isZInsideFrustum(&primitive->at(start + 2));
}

bool CullingJob::isXYInsideFrustum(glm::vec4* point) {
	const auto x = point->x;
	const auto y = point->y;
	const auto w = point->w;

	return ((-w <= x) && (x <= w)) &&
		((-w <= y) && (y <= w)) &&
		(0 < w);
}

bool CullingJob::isZInsideFrustum(glm::vec4* point) {
	const auto z = point->z;
	const auto w = point->w;

	return ((-w <= z) && (z <= w)) ||
		(0 < w);
}

bool CullingJob::backfaceCullingTest(std::vector<glm::vec4>* primitive, size_t start) {
	const auto p1 = glm::vec3(primitive->at(start));
	const auto p2 = glm::vec3(primitive->at(start + 1));
	const auto p3 = glm::vec3(primitive->at(start + 2));
	const auto normal = glm::triangleNormal(p1, p2, p3);
	const auto n = glm::dot(normal, p1);

	if (!*Config::getInstance()->getCW()) {
		return n < 0.0f;
	}
	return n > 0.0f;
}
