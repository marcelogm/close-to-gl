#include "services.hpp"

VertexData* ModelToVertex::getVertexDataFromDataModel(Model* model) {
	const auto size = model->getTriangles()->size() * 3;
	VertexData* vertices = (VertexData*)malloc(size * sizeof(VertexData));
	auto i = 0;

	for (const auto triangle : *model->getTriangles()) {
		for (const auto vertex : *triangle->getVertices()) {
			auto position = vertex->getPosition();
			auto normal = vertex->getNormal();
			auto color = vertex->getColor();
			vertices[i] = {
				{ position->x, position->y, position->z },
				{ normal->x, normal->y, normal->z },
				{ color->r, color->g, color->b }
			};
			i++;
		}
	}
	return vertices;
}

VertexDataRange ModelToVertex::getRange(VertexData* vertices, size_t size) {
	float minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;
	for (auto i = 0; i < size; i++) {
		minX = (glm::min)(minX, vertices[i].position[0]);
		minY = (glm::min)(minY, vertices[i].position[1]);
		minZ = (glm::min)(minZ, vertices[i].position[2]);
		maxX = (glm::max)(maxX, vertices[i].position[0]);
		maxY = (glm::max)(maxY, vertices[i].position[1]);
		maxZ = (glm::max)(maxZ, vertices[i].position[2]);
	}
	return {
		glm::vec2(minX, maxX), glm::vec2(minY, maxY), glm::vec2(minZ, maxZ)
	};
}