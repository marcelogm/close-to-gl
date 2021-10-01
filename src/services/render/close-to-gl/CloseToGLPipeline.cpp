#include "close.hpp"

using namespace close;
#define MAX_VERTEX_COUNT 100000

std::unique_ptr<std::vector<unsigned char>> CloseToGLPipeline::apply(data::VertexData* vertices, size_t size) {
	const auto count = this->toHomogeneousClipSpace->apply(vertices, size);
	const auto clipped = this->culling->apply(count);
	const auto viewported = this->normalization->apply(clipped);
	return std::make_unique< std::vector<unsigned char>>(this->raster->apply(viewported));

}

CloseToGLPipeline::CloseToGLPipeline() {
	this->buffer = (VertexPayload *)malloc(sizeof(VertexPayload) * MAX_VERTEX_COUNT);
	this->toHomogeneousClipSpace = new VertexShader(buffer);
	this->culling = new FaceCulling(buffer);
	this->normalization = new PerspectiveAndViewport(buffer);
	this->raster = new RasterJob(buffer);
}


