#include "raster.h"

using namespace close;
using std::swap;
using std::tie;

Rasterizer::Rasterizer(VertexPayload* buffer) {
	this->scanner = new Scanner();
	this->buffer = buffer;
	this->config = Config::getInstance();
}

vector<unsigned char> close::Rasterizer::apply(size_t count) {
	const auto width = *config->getWindowWidth();
	const auto height = *config->getWindowHeight();

	auto outputBuffer = RgbBuffer(width, height);
	auto zBuffer = (float*)malloc(sizeof(float) * width * height);
	std::fill_n(zBuffer, width * height, 1.0f);

	for (size_t i = 0; i < count; i += 3) {
		const auto v = buffer + i;
		this->draw(&outputBuffer, zBuffer, v, v + 1, v + 2);
	}

	free(zBuffer);

	return outputBuffer.get();
}

void Rasterizer::draw(RgbBuffer* buffer, float* zBuffer, data::VertexPayload* v0, data::VertexPayload* v1, data::VertexPayload* v2) {
	this->floor(v0); 
	this->floor(v1); 
	this->floor(v2);

	this->order(v0, v1, v2);

	if (v0->position.x == v2->position.x) {
		return;
	}

	vector<Slope> sides[2];
	bool isTheShorterSide = this->isTheShorterSide(&v0->position, &v1->position, &v2->position);
	sides[!isTheShorterSide] = createSlope(v0, v2);

	for (auto x = v0->position.x, end = v0->position.x; ; ++x) {
		if (x >= end) {
			if (x >= v2->position.x) break;
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

vector<Slope> Rasterizer::createSlope(data::VertexPayload* start, data::VertexPayload* end) {
	vector<Slope> slopes(PROPS_SLOPE_COUNT);
	const auto steps = end->position.x - start->position.x;
	const auto zStart = 1.f / start->position.z;
	const auto zEnd = 1.f / end->position.z;
	slopes.at(0) = Slope(start->position.y, end->position.y, steps);
	slopes.at(1) = Slope(start->color.r * zStart, end->color.r * zEnd, steps);
	slopes.at(2) = Slope(start->color.g * zStart, end->color.g * zEnd, steps);
	slopes.at(3) = Slope(start->color.b * zStart, end->color.b * zEnd, steps);
	slopes.at(4) = Slope(zStart, zEnd, steps);
	return slopes;
}

bool Rasterizer::isTheShorterSide(glm::vec4* p0, glm::vec4* p1, glm::vec4* p2) {
	return (p1->x - p0->x) * (p2->y - p0->y) < (p1->y - p0->y) * (p2->x - p0->x);
}

void Rasterizer::floor(data::VertexPayload* vertex) {
	vertex->position.y = std::floor(vertex->position.y);
	vertex->position.x = std::floor(vertex->position.x);
}

void Rasterizer::order(data::VertexPayload* v0, data::VertexPayload* v1, data::VertexPayload* v2) {
	if (tie(v1->position.x, v1->position.y) < tie(v0->position.x, v0->position.y)) {
		swap(v0->position, v1->position);
		swap(v0->color, v1->color);
	}
	if (tie(v2->position.x, v2->position.y) < tie(v0->position.x, v0->position.y)) {
		swap(v0->position, v2->position);
		swap(v0->color, v2->color);
	}
	if (tie(v2->position.x, v2->position.y) < tie(v1->position.x, v1->position.y)) {
		swap(v1->position, v2->position);
		swap(v1->color, v2->color);
	}
}
