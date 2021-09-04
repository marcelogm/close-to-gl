#include "close.hpp"

using namespace close;

std::unique_ptr<std::vector<VertexData2D>> CloseToGLPipeline::apply(std::vector<VertexData>* vertices) {
	std::unique_ptr<std::vector<VertexData2D>> v(new std::vector<VertexData2D>());
	v->push_back({ { -0.90f, -0.90f }, { 255,   0,   0 } });
	v->push_back({ {  0.90f, -0.90f }, {   0, 255,   0 } });
	v->push_back({ {  0.00f,  0.90f }, {   0,   0, 255 } });
	return v;
}

CloseToGLPipeline::CloseToGLPipeline() {
	this->toHomogeneousClipSpace = std::unique_ptr<VertexShaderJob>();
	this->clipping = std::unique_ptr<ClippingJob>();
	this->normalization = std::unique_ptr<PerspectiveDivideJob>();
	this->toViewport = std::unique_ptr<ViewportTransformJob>();
}


