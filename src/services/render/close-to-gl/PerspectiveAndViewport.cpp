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
		buffer[i] = this->transform(width, height, &buffer[i]);
	}
	return count;
};

VertexPayload PerspectiveAndViewport::transform(size_t width, size_t height, VertexPayload* payload) {
	const auto w = payload->position.w;
	return {
		vec4(
			((payload->position.x / w) + 1) * 0.5f * width,
			((payload->position.y / w) + 1) * 0.5f * height,
			payload->position.z / w,
			1.0f / w
		),
		payload->normal / w,
		payload->texture / w,
		payload->color / w
	};
}

