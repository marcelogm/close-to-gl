#include "filter.h";

using namespace filter;

BilinearResampling::BilinearResampling() {
	config = Config::getInstance();
}

vec3 filter::BilinearResampling::apply(data::Texture* texture, float x, float y, vec3 color, float deltaX, float deltaY) {
	const auto coordX = (texture->width - 1) * x;
	const auto coordY = (texture->width - 1) * y;

	const int x0 = std::floorl(coordX);
	const int y0 = std::floorl(coordY);
	const int x1 = x0 + 1;
	const int y1 = y0 + 1;

	const float dx = coordX - x0;
	const float dy = coordY - y0;

	const vec3 t00 = this->getTexturePixel(texture, x0, y0);
	const vec3 t10 = this->getTexturePixel(texture, x1, y0);
	const vec3 t01 = this->getTexturePixel(texture, x0, y1);
	const vec3 t11 = this->getTexturePixel(texture, x1, y1);

	const vec3 filtered = (1 - dx) * (1 - dy) * t00 +
		dx * (1 - dy) * t10 +
		(1 - dx) * dy * t01 +
		dx * dy * t11;
	return filtered * color;
}

vec3 filter::BilinearResampling::getTexturePixel(data::Texture* texture, int x, int y) {
	const int offset = (y * texture->width * 3) + (x * 3);
	return vec3(
		texture->data[offset],
		texture->data[offset + 1],
		texture->data[offset + 2]
	);
}


bool filter::BilinearResampling::matches() {
	return *config->getTextureUse() == 1 &&
		*config->getFiltering() == BILINEAR_RESAMPLING;
}
