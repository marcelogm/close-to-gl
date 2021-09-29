#include "close.hpp"

using namespace close;

std::unique_ptr<std::vector<unsigned char>> CloseToGLPipeline::apply(std::vector<data::VertexData>* vertices) {
	auto homogeneous = this->toHomogeneousClipSpace->apply(vertices);
	auto clipped = this->culling->apply(&homogeneous);
	auto normalized = this->normalization->apply(&clipped);
	auto viewported = this->viewport->apply(&normalized);
	return std::make_unique< std::vector<unsigned char>>(this->raster->apply(&viewported));
}

CloseToGLPipeline::CloseToGLPipeline() {
	this->toHomogeneousClipSpace = new VertexShaderJob();
	this->culling = new CullingJob();
	this->normalization = new PerspectiveDivideJob();
	this->viewport = new ViewportTransformationJob();
	this->raster = new RasterJob();
}


