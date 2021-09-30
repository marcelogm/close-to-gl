#include "close.hpp"

using namespace close;
#define MAX_VERTEX_COUNT 100000

std::unique_ptr<std::vector<unsigned char>> CloseToGLPipeline::apply(std::vector<data::VertexData>* vertices) {
	auto count = this->toHomogeneousClipSpace->apply(vertices);
	auto clipped = this->culling->apply(count);
	auto viewported = this->normalization->apply(clipped);
	return std::make_unique< std::vector<unsigned char>>(this->raster->apply(viewported));

}

CloseToGLPipeline::CloseToGLPipeline() {
	this->buffer = new vector<VertexPayload>(MAX_VERTEX_COUNT);
	this->toHomogeneousClipSpace = new VertexShader(buffer);
	this->culling = new CullingJob(buffer);
	this->normalization = new PerspectiveAndViewport(buffer);
	this->raster = new RasterJob(buffer);
}


