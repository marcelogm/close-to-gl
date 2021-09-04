#include "close.hpp"

using namespace close;

std::vector<data::VertexData2D> ViewportTransformJob::apply(std::vector<glm::vec3>) {
	return std::vector<data::VertexData2D>({
		{ 1.0f, 1.0f }, 
		{ 1, 1, 1 }
	});
};