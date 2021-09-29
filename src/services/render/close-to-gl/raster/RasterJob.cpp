#include "raster.h"

using namespace close;


std::vector<unsigned char> close::RasterJob::apply(std::vector<data::VertexPayload>* payload) {
	auto config = Config::getInstance();
	auto width = *config->getWindowWidth();
	auto height = *config->getWindowHeight();
	auto buffer = RgbBuffer(width, height);

	for (size_t i = 0; i < payload->size(); i += 3) {
		auto v0 = payload->at(i);
		auto v1 = payload->at(i + 1);
		auto v2 = payload->at(i + 2);
		this->draw(&buffer, &v0, &v1, &v2);
	}

	return buffer.get();
}

void RasterJob::draw(RgbBuffer* buffer, data::VertexPayload* v0, data::VertexPayload* v1, data::VertexPayload* v2) {
	auto p0 = this->extract(v0);
	auto p1 = this->extract(v1);
	auto p2 = this->extract(v2);

	this->order(v0, v1, v2, &p0, &p1, &p2);

	if (p0.y == p2.y) {
		return;
	}

	std::vector<Slope> sides[2];
	bool isTheShorterSide = this->isTheShorterSide(&p0, &p1, &p2);
	
	sides[!isTheShorterSide] = createSlope(&p0, &p2, v0, v2, p2.y - p0.y);

	for (auto y = p0.y, end = p0.y; ; ++y) {
		if (y >= end) {
			if (y >= p2.y) {
				break;
			}
			if (y < p1.y) {
				end = p1.y;
				sides[isTheShorterSide] = createSlope(&p0, &p1, v0, v1, (end - p0.y));
			} else {
				end = p2.y;
				sides[isTheShorterSide] = createSlope(&p1, &p2, v1, v2, (end - p1.y));
			}
		}
		this->scanner->scanline(buffer, y, &sides[0], &sides[1]);
	}
}

std::vector<Slope> RasterJob::createSlope(glm::vec3* p0, glm::vec3* p1, data::VertexPayload* start, data::VertexPayload* end, int steps) {
	std::vector<Slope> slopes;
	slopes.push_back(Slope(p0->x, p1->x, steps));
	slopes.push_back(Slope(start->color.r, end->color.r, steps));
	slopes.push_back(Slope(start->color.g, end->color.g, steps));
	slopes.push_back(Slope(start->color.b, end->color.b, steps));
	return slopes;
}

bool RasterJob::isTheShorterSide(glm::vec3* p0, glm::vec3* p1, glm::vec3* p2) {
	return (p1->y - p0->y) * (p2->x - p0->x) < (p1->x - p0->x) * (p2->y - p0->y);
}

glm::vec3 RasterJob::extract(data::VertexPayload* vertex) {
	return glm::vec3(
		(int) std::floor(vertex->position.x),
		(int) std::floor(vertex->position.y),
		(int) std::floor(vertex->position.z)
	);
}

void RasterJob::order(data::VertexPayload* v0, data::VertexPayload* v1, data::VertexPayload* v2,
	glm::vec3* p0, glm::vec3* p1, glm::vec3* p2) {

	if (std::tie(p1->y, p1->x) < std::tie(p0->y, p0->x)) {
		std::swap(p0->x, p1->x); std::swap(p0->y, p1->y); std::swap(v0, v1);
	}
	if (std::tie(p2->y, p2->x) < std::tie(p0->y, p0->x)) {
		std::swap(p0->x, p2->x); std::swap(p0->y, p2->y); std::swap(v0, v2);
	}
	if (std::tie(p2->y, p2->x) < std::tie(p1->y, p1->x)) {
		std::swap(p1->x, p2->x); std::swap(p1->y, p2->y); std::swap(v1, v2);
	}
}

RasterJob::RasterJob() {
	this->scanner = new Scanner();
}

