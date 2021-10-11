#include "filter.h"

using namespace filter;

NoTexture::NoTexture() {
	config = Config::getInstance();
}

bool NoTexture::matches() {
	return *config->getTextureUse() == 0;
}

vec3 NoTexture::apply(data::Texture* texture, float x, float y, vec3 color, float deltaX, float deltaY) {
	return vec3(
		color.r * 255.0f,
		color.g * 255.0f,
		color.b * 255.0f
	);
}