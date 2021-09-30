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

	if (v0->position.x == v2->position.x) {
		return;
	}

	std::vector<Slope> sides[2];
	bool isTheShorterSide = this->isTheShorterSide(&v0->position, &v1->position, &v2->position);
	
	sides[!isTheShorterSide] = createSlope(v0, v2);

	for (auto x = v0->position.x, end = v0->position.x; ; ++x) {
		if (x >= end) {
			if (x >= v2->position.x) {
				break;
			}
			if (x < v1->position.x) {
				end = v1->position.x;
				sides[isTheShorterSide] = createSlope(v0, v1);
			} else {
				end = v2->position.x;
				sides[isTheShorterSide] = createSlope(v1, v2);
			}
		}
		this->scanner->scanline(buffer, zBuffer, x, &sides[0], &sides[1]);
	}
}

std::vector<Slope> RasterJob::createSlope(data::VertexPayload* start, data::VertexPayload* end) {
	std::vector<Slope> slopes;
	float steps = end->position.x - start->position.x;
	float zStart = 1.f / start->position.z;
	float zEnd = 1.f / end->position.z;
	slopes.push_back(Slope(start->position.y, end->position.y, steps));
	slopes.push_back(Slope(start->color.r * zStart, end->color.r * zEnd, steps));
	slopes.push_back(Slope(start->color.g * zStart, end->color.g * zEnd, steps));
	slopes.push_back(Slope(start->color.b * zStart, end->color.b * zEnd, steps));
	slopes.push_back(Slope(zStart, zEnd, steps));
	return slopes;
}

bool RasterJob::isTheShorterSide(glm::vec4* p0, glm::vec4* p1, glm::vec4* p2) {
	return (p1->x - p0->x) * (p2->y - p0->y) < (p1->y - p0->y) * (p2->x - p0->x);
}

void RasterJob::floor(data::VertexPayload* vertex) {
	vertex->position.y = std::floor(vertex->position.y);
	vertex->position.x = std::floor(vertex->position.x);
}

void RasterJob::order(data::VertexPayload* v0, data::VertexPayload* v1, data::VertexPayload* v2) {
	if (std::tie(v1->position.x, v1->position.y) < std::tie(v0->position.x, v0->position.y)) {
		std::swap(v0->position, v1->position);
		std::swap(v0->color, v1->color);
	}
	if (std::tie(v2->position.x, v2->position.y) < std::tie(v0->position.x, v0->position.y)) {
		std::swap(v0->position, v2->position);
		std::swap(v0->color, v2->color);
	}
	if (std::tie(v2->position.x, v2->position.y) < std::tie(v1->position.x, v1->position.y)) {
		std::swap(v1->position, v2->position);
		std::swap(v1->color, v2->color);
	}
}


RasterJob::RasterJob() {
	this->scanner = new Scanner();
}

