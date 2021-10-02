#include "close.hpp"

using namespace close;
#define MAX_VERTEX_COUNT 100000

vector<unsigned char> CloseToGLPipeline::apply(data::VertexData* vertices, size_t size) {
	const auto count = this->vertexShader->apply(vertices, size);
	const auto clipped = this->culling->apply(count);
	const auto viewported = this->normalization->apply(clipped);
	return this->raster->apply(viewported);

}

CloseToGLPipeline::CloseToGLPipeline() {
	this->buffer = (VertexPayload *)malloc(sizeof(VertexPayload) * MAX_VERTEX_COUNT);
	this->vertexShader = new VertexShader(buffer);
	this->culling = new FaceCulling(buffer);
	this->normalization = new PerspectiveAndViewport(buffer);
	this->raster = new Rasterizer(buffer);
}


