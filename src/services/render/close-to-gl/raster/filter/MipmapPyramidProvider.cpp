#include "filter.h";

using namespace filter;

MipmapPyramidProvider* MipmapPyramidProvider::instance = nullptr;

MipmapPyramidProvider* filter::MipmapPyramidProvider::getInstance()
{
	if (instance == nullptr) {
		instance = new MipmapPyramidProvider();
	}
	return instance;
}

void MipmapPyramidProvider::create(Texture* texture) {
	// :( que coisa mais feia
	Texture* current = new Texture();
	current->width = texture->width;
	current->height = texture->height;
	current->data = (BYTE*)malloc(texture->width * texture->height * 3 * sizeof(BYTE));
	memcpy(current->data, texture->data, texture->width * texture->height * 3 * sizeof(BYTE));

	mipmap = new TextureMipmap(MIPMAP_LEVEL_COUNT);
	for (size_t i = 0; i < MIPMAP_LEVEL_COUNT; i++) {
		#ifdef DEBUG
			stbi_write_jpg(std::format("mipmap_level_{}.jpg", i).c_str(), current->width, current->height, 3, current->data, 100);
		#endif
		mipmap->setLevel(i, current);
		current = getNextLevel(current);
	}
}

Texture* MipmapPyramidProvider::getNextLevel(Texture* texture) {
	Texture* next = new Texture();
	if (texture->width != texture->height) {
		throw new std::exception("not implemented yet");
	}
	
	next->width = texture->width / 2;
	next->height = texture->height / 2;
	next->data = (unsigned char *)malloc(next->width * next->height * 3 * sizeof(unsigned char));

	for (int i = 0; i < next->width; i++) {
		for (int j = 0; j < next->height; j++) {
			const auto x = i * 2;
			const auto y = j * 2;
			next->data[(i * next->width * 3) + (j * 3)] = this->getTexelAverage(texture, x, y, 0);
			next->data[(i * next->width * 3) + (j * 3) + 1] = this->getTexelAverage(texture, x, y, 1);
			next->data[(i * next->width * 3) + (j * 3) + 2] = this->getTexelAverage(texture, x, y, 2);
		}
	}
	return next;
}

BYTE MipmapPyramidProvider::getTexelAverage(Texture* texture, int x, int y, int offset) {
	return (
		texture->data[(x * texture->width * 3) + (y * 3) + offset] +
		texture->data[((x + 1) * texture->width * 3) + (y * 3) + offset] +
		texture->data[(x * texture->width * 3) + ((y + 1) * 3) + offset] +
		texture->data[((x + 1) * texture->width * 3) + ((y + 1) * 3) + offset]
	) / 4;
}

Texture* filter::MipmapPyramidProvider::get(size_t level) {
	return this->mipmap->getLevel(level);
}

TextureMipmap::TextureMipmap(size_t levels) {
	this->pyramid = vector<Texture*>(levels);
}

Texture* TextureMipmap::getLevel(size_t level) {
	return pyramid.at(level);
}

void TextureMipmap::setLevel(size_t level, Texture* texture) {
	pyramid.at(level) = texture;
}
