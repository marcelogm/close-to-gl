#include "services.hpp"
#include "render/close-to-gl/raster/filter/filter.h"

data::Texture TextureProvider::get() {
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("data/mandrill_256.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		Texture texture = { (size_t)width, (size_t)height, data };
		filter::MipmapPyramidProvider::getInstance()->create(&texture);
		return texture;
	}
	return { 0, 0, nullptr };
}

TextureProvider::TextureProvider() {}