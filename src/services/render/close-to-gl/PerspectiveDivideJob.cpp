#include "close.hpp"

using namespace close;

PerspectiveAndViewport::PerspectiveAndViewport(VertexPayload* buffer) {
	this->config = Config::getInstance();
	this->buffer = buffer;
}

size_t PerspectiveAndViewport::apply(size_t count) {
	const float width = (float)*config->getWindowWidth();
	const float height = (float)*config->getWindowHeight();
	for (size_t i = 0; i < count; i++) {
		auto vertex = buffer[i];
		auto transformed = this->transform(width, height, vertex.position);
		buffer[i] = {
			transformed,
			vertex.normal,
			vertex.color
		};
	}
	return count;
};

vec4 PerspectiveAndViewport::transform(size_t width, size_t height, vec4 vertex) {
	return vec4(
		((vertex.x / vertex.w) + 1) * 0.5f * width,
		((vertex.y / vertex.w) + 1) * 0.5f * height,
		vertex.z / vertex.w,
		1.0f / vertex.w
	);
}

