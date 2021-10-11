#include "filter.h"

using namespace filter;

NearestNeighborResampling::NearestNeighborResampling() {
	config = Config::getInstance();
}

vec3 filter::NearestNeighborResampling::apply(data::Texture* texture, float x, float y, vec3 color, float deltaX, float deltaY) {
	const int textureX = std::roundl((texture->width - 1) * x);
	const int textureY = std::roundl((texture->height - 1) * y);
	return vec3(
		texture->data[(textureY * texture->width * 3) + (textureX * 3)] * color.r,
		texture->data[(textureY * texture->width * 3) + (textureX * 3) + 1] * color.g,
		texture->data[(textureY * texture->width * 3) + (textureX * 3) + 2] * color.b
	);
}

bool filter::NearestNeighborResampling::matches() {
	return *config->getTextureUse() == 1 &&
		*config->getFiltering() == NEAREST_NEIGHBOR_RESAMPLING;
}
