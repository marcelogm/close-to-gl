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

	if (v0->position.y == v2->position.y) {
		return;
	}

	vector<Slope> sides[2];
	bool isTheShorterSide = this->isTheShorterSide(&v0->position, &v1->position, &v2->position);
	sides[!isTheShorterSide] = createSlope(v0, v2);

	for (auto y = v0->position.y, end = v0->position.y; ; ++y) {
		if (y >= end) {
			if (y >= v2->position.y) break;
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

vector<Slope> Rasterizer::createSlope(data::VertexPayload* start, data::VertexPayload* end) {
	vector<Slope> slopes(PROPS_SLOPE_COUNT);
	const auto steps = end->position.y - start->position.y;
	slopes.at(0) = Slope(start->position.x, end->position.x, steps);
	slopes.at(1) = Slope(start->color.r, end->color.r, steps);
	slopes.at(2) = Slope(start->color.g, end->color.g, steps);
	slopes.at(3) = Slope(start->color.b, end->color.b, steps);
	slopes.at(4) = Slope(start->texture.x, end->texture.x, steps);
	slopes.at(5) = Slope(start->texture.y, end->texture.y, steps);
	slopes.at(6) = Slope(start->position.z, end->position.z, steps);
	slopes.at(7) = Slope(start->position.w, end->position.w, steps);
	return slopes;
}

bool Rasterizer::isTheShorterSide(glm::vec4* p0, glm::vec4* p1, glm::vec4* p2) {
	return (p1->y - p0->y) * (p2->x - p0->x) < (p1->x - p0->x) * (p2->y - p0->y);
}

void Rasterizer::floor(data::VertexPayload* vertex) {
	vertex->position.x = std::ceil(vertex->position.x);
	vertex->position.y = std::ceil(vertex->position.y);
}

void Rasterizer::order(data::VertexPayload* v0, data::VertexPayload* v1, data::VertexPayload* v2) {
	if (tie(v1->position.y, v1->position.x) < tie(v0->position.y, v0->position.x)) {
		swap(v0->position, v1->position);
		swap(v0->color, v1->color);
		swap(v0->texture, v1->texture);
	}
	if (tie(v2->position.y, v2->position.x) < tie(v0->position.y, v0->position.x)) {
		swap(v0->position, v2->position);
		swap(v0->color, v2->color);
		swap(v0->texture, v2->texture);
	}
	if (tie(v2->position.y, v2->position.x) < tie(v1->position.y, v1->position.x)) {
		swap(v1->position, v2->position);
		swap(v1->color, v2->color);
		swap(v1->texture, v2->texture);
	}
}
