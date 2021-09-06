#include "close.hpp"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

using namespace close;

std::unique_ptr<std::vector<data::VertexData2D>> CloseToGLPipeline::apply(std::vector<data::VertexData>* vertices) {
	auto homogeneous = this->toHomogeneousClipSpace->apply(vertices);
	auto clipped = this->clipping->apply(&homogeneous);
	auto normalized = this->normalization->apply(&clipped);
	return std::make_unique<std::vector<data::VertexData2D>>(normalized);
}

CloseToGLPipeline::CloseToGLPipeline() {
	this->toHomogeneousClipSpace = new VertexShaderJob();
	this->clipping = new ClippingJob();
	this->normalization = new PerspectiveDivideJob();
}


