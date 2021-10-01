#include "close.hpp"
#include <glm/gtx/normal.hpp>

using namespace close;

#define TRIANGLE_VERTICES 3

FaceCulling::FaceCulling(VertexPayload* buffer) {
	this->buffer = buffer;
}

size_t FaceCulling::apply(size_t verticeCount) {
	size_t surviving = 0;
	for (size_t i = 0; i < verticeCount; i += 3) {
		if (!shouldDiscard(i)) {
			buffer[surviving] = buffer[i];
			buffer[surviving + 1] = buffer[i + 1];
			buffer[surviving + 2] = buffer[i + 2];
			surviving += 3;
		}
		else {
			int a = 2;
		}
	}
	return surviving;
}

bool FaceCulling::shouldDiscard(size_t at) {
	return this->backfaceCullingTest(at) || this->atLeastOneVerticeOutsideFrustum(at);
}

bool FaceCulling::atLeastOneVerticeOutsideFrustum(size_t at) {
	return !this->isInsideFrustum(&buffer[at].position) ||
		!this->isInsideFrustum(&buffer[at + 1].position) ||
		!this->isInsideFrustum(&buffer[at + 2].position);
}

bool FaceCulling::isInsideFrustum(glm::vec4* point) {
	const auto x = point->x;
	const auto y = point->y;
	const auto w = point->w;
	const auto z = point->z;
	
	return ((-w <= x) && (x <= w)) &&
		((-w <= y) && (y <= w)) &&
		((-w <= z) && (z <= w)) && 
		(0 < w);
}

bool FaceCulling::backfaceCullingTest(size_t at) {
	const auto p1 = vec3(buffer[at].position);
	const auto p2 = vec3(buffer[at + 1].position);
	const auto p3 = vec3(buffer[at + 2].position);
	const auto normal = glm::triangleNormal(p1, p2, p3);
	const auto n = glm::dot(normal, p1);

	if (!*Config::getInstance()->getCW()) {
		return n < 0.0f;
	}
	return n > 0.0f;
}

