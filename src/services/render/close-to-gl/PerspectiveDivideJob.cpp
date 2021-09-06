#include "close.hpp"

using namespace close;

std::vector<data::VertexData2D> PerspectiveDivideJob::apply(std::vector<glm::vec4>* vertices) {
	std::vector<data::VertexData2D> positions(vertices->size());
	for (size_t i = 0; i < vertices->size(); i++) {
		const auto w = vertices->at(i).w;
		positions[i] = {
			vertices->at(i).x / w,
			vertices->at(i).y / w 
		};
	}
	return positions;
};

