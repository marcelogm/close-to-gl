#include "close.hpp"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

using namespace close;

std::unique_ptr<std::vector<data::VertexData2D>> CloseToGLPipeline::apply(std::vector<data::VertexData>* vertices) {
	auto homogeneous = this->toHomogeneousClipSpace->apply(vertices);
	auto clipped = this->clipping->apply(homogeneous);

	std::unique_ptr<std::vector<data::VertexData2D>> v(new std::vector<data::VertexData2D>());
	if (clock() % 2 == 0) {
		v->push_back({ { -0.90f, -0.90f }, { 255,   0,   0 } });
		v->push_back({ {  0.95f, -0.90f }, {   0, 255,   0 } });
		v->push_back({ {  0.50f,  0.50f }, {   0,   0, 255 } });
	}
	v->push_back({ { -0.40f, -0.90f }, { 255,   0,   0 } });
	v->push_back({ {  0.90f, -0.90f }, {   0, 255,   0 } });
	v->push_back({ {  0.00f,  0.90f }, {   0,   0, 255 } });
	return v;
}

CloseToGLPipeline::CloseToGLPipeline() {
	this->toHomogeneousClipSpace = new VertexShaderJob();
	this->clipping = new ClippingJob();
	this->normalization = new PerspectiveDivideJob();
	this->toViewport = new ViewportTransformJob();
}


