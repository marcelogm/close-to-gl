#include "raster.h"

using namespace close;


std::vector<unsigned char> close::RasterJob::apply(std::vector<data::VertexPayload>* payload) {
	auto config = Config::getInstance();
	auto width = *config->getWindowWidth();
	auto height = *config->getWindowHeight();
	auto buffer = RgbBuffer(width, height);
	auto zBuffer = std::vector<float>(width * height);
	std::fill_n(&zBuffer.front(), width * height, 1.0f);

	for (size_t i = 0; i < payload->size(); i += 3) {
		auto v0 = payload->at(i);
		auto v1 = payload->at(i + 1);
		auto v2 = payload->at(i + 2);
		this->draw(&buffer, &zBuffer, &v0, &v1, &v2);
	}

	return buffer.get();
}

void RasterJob::draw(RgbBuffer* buffer, std::vector<float>* zBuffer, data::VertexPayload* v0, data::VertexPayload* v1, data::VertexPayload* v2) {
	this->floor(v0); 
	this->floor(v1); 
	this->floor(v2);

	this->order(v0, v1, v2);

	if (v0->position.y == v2->position.y) {
		return;
	}

	std::vector<Slope> sides[2];
	bool isTheShorterSide = this->isTheShorterSide(&v0->position, &v1->position, &v2->position);
	
	sides[!isTheShorterSide] = createSlope(v0, v2);

	for (auto y = v0->position.y, end = v0->position.y; ; ++y) {
		if (y >= end) {
			if (y >= v2->position.y) {
				break;
			}
			if (y < v1->position.y) {
				end = v1->position.y;
				sides[isTheShorterSide] = createSlope(v0, v1);
			} else {
				end = v2->position.y;
				sides[isTheShorterSide] = createSlope(v1, v2);
			}
		}
		this->scanner->scanline(buffer, zBuffer, y, &sides[0], &sides[1]);
	}
}

std::vector<Slope> RasterJob::createSlope(data::VertexPayload* start, data::VertexPayload* end) {
	std::vector<Slope> slopes;
	float steps = end->position.y - start->position.y;
	float zStart = 1.f / start->position.z;
	float zEnd = 1.f / end->position.z;
	slopes.push_back(Slope(start->position.x, end->position.x, steps));
	slopes.push_back(Slope(start->color.r * zStart, end->color.r * zEnd, steps));
	slopes.push_back(Slope(start->color.g * zStart, end->color.g * zEnd, steps));
	slopes.push_back(Slope(start->color.b * zStart, end->color.b * zEnd, steps));
	slopes.push_back(Slope(zStart, zEnd, steps));
	return slopes;
}

bool RasterJob::isTheShorterSide(glm::vec4* p0, glm::vec4* p1, glm::vec4* p2) {
	return (p1->y - p0->y) * (p2->x - p0->x) < (p1->x - p0->x) * (p2->y - p0->y);
}

void RasterJob::floor(data::VertexPayload* vertex) {
	vertex->position.x = std::floor(vertex->position.x);
	vertex->position.y = std::floor(vertex->position.y);
}

void RasterJob::order(data::VertexPayload* v0, data::VertexPayload* v1, data::VertexPayload* v2) {
	if (std::tie(v1->position.y, v1->position.x) < std::tie(v0->position.y, v0->position.x)) {
		std::swap(v0->position, v1->position);
		std::swap(v0->color, v1->color);
	}
	if (std::tie(v2->position.y, v2->position.x) < std::tie(v0->position.y, v0->position.x)) {
		std::swap(v0->position, v2->position);
		std::swap(v0->color, v2->color);
	}
	if (std::tie(v2->position.y, v2->position.x) < std::tie(v1->position.y, v1->position.x)) {
		std::swap(v1->position, v2->position);
		std::swap(v1->color, v2->color);
	}
}


RasterJob::RasterJob() {
	this->scanner = new Scanner();
}

