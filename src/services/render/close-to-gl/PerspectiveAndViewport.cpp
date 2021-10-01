#include "close.hpp"

using namespace close;

PerspectiveAndViewport::PerspectiveAndViewport(VertexPayload* buffer) {
	this->config = Config::getInstance();
	this->buffer = buffer;
}

size_t PerspectiveAndViewport::apply(size_t count) {
	const auto width = *config->getWindowWidth();
	const auto height = *config->getWindowHeight();
	for (size_t i = 0; i < count; i++) {
		buffer[i].position = this->transform(width, height, &buffer[i].position);
	}
	return count;
};

vec4 PerspectiveAndViewport::transform(size_t width, size_t height, vec4* vertex) {
	const auto w = vertex->w;
	return vec4(
		((vertex->x / w) + 1) * 0.5f * width,
		((vertex->y / w) + 1) * 0.5f * height,
		vertex->z / w,
		1.0f / w
	);
}

