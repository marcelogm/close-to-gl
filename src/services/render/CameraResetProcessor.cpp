#include "render.hpp"

using namespace renderer;

void CameraResetProcessor::process(data::VertexDataRange range) {
	if (camera->getResetRequest()) {
		camera->reset(range.x, range.y);
	}
}

CameraResetProcessor::CameraResetProcessor() {
	this->camera = Camera::getInstance();
}