#include "services.hpp"

data::Texture TextureProvider::get() {
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("data/mandrill_256.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		return { (size_t)width, (size_t)height, data };
	}
	return { 0, 0, nullptr };
}

TextureProvider::TextureProvider() {}