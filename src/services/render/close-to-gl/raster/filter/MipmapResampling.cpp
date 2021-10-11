#include "filter.h"
#include <math.h>

using namespace filter;


filter::MipmapResampling::MipmapResampling() {
	config = Config::getInstance();
	mipmapProvider = MipmapPyramidProvider::getInstance();
	bilinear = new BilinearResampling();
}

vec3 filter::MipmapResampling::apply(Texture* texture, float x, float y, vec3 color, float deltaX, float deltaY) {
	float level = this->getMipmapLevel(deltaX, deltaY, texture->width, texture->height);
	float floor = floorl(level);
	if ((level + 1) < MIPMAP_LEVEL_COUNT) {
		Texture* currentLevel = this->mipmapProvider->get(floor);
		Texture* nextLevel = this->mipmapProvider->get(floor + 1);
		const vec3 current = bilinear->apply(currentLevel, x, y, color, deltaX, deltaY);
		const vec3 next = bilinear->apply(nextLevel, x, y, color, deltaX, deltaY);
		const float nextWeight = (level - floor);
		const float currentWeight = 1 - nextWeight;
		return ((current * currentWeight) + (next * nextWeight));
	}
	return vec3(1.0f, 1.0f, 1.0f);
}

float filter::MipmapResampling::getMipmapLevel(float deltaX, float deltaY, int width, int height) {
	return abs((log((std::max)((abs(deltaX) * width), (abs(deltaY) * height))) / log(2.0)));
}

bool filter::MipmapResampling::matches() {
	return *config->getTextureUse() == 1 &&
		*config->getFiltering() == MIP_MAPPING_RESAMPLING;
}
