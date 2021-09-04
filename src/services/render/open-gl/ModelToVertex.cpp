#include "open.hpp"

using namespace open;

std::vector<VertexData>* ModelToVertex::getVertexDataFromDataModel(data::Model* model) {
	std::vector<VertexData>* vertices = new std::vector<VertexData>();
	for (auto triangle : *model->getTriangles()) {
		for (auto vertex : *triangle->getVertices()) {
			auto position = vertex->getPosition();
			auto normal = vertex->getNormal();
			auto color = vertex->getColor();
			vertices->push_back({
				{ position->x, position->y, position->z },
				{ normal->x, normal->y, normal->z },
				{ color->r, color->g, color->b }
			});
		}
	}
	return vertices;
}

#undef max 
#undef min
VertexDataRange ModelToVertex::getRange(std::vector<VertexData>* vertices) {
	float minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;
	for (VertexData vertex : *vertices) {
		minX = glm::min(minX, vertex.position[0]);
		minY = glm::min(minY, vertex.position[1]);
		minZ = glm::min(minZ, vertex.position[2]);
		maxX = glm::max(maxX, vertex.position[0]);
		maxY = glm::max(maxY, vertex.position[1]);
		maxZ = glm::max(maxZ, vertex.position[2]);
	}
	return {
		glm::vec2(minX, maxX), glm::vec2(minY, maxY), glm::vec2(minZ, maxZ)
	};
}