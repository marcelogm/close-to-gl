#include "raster.h"

using namespace close;

#define RGB_CHANNEL_COUNT 3
#define DEBUG 1

RgbBuffer::RgbBuffer(size_t width, size_t height) {
	this->width = width;
	this->height = height;
	const auto size = width * height * RGB_CHANNEL_COUNT;
	this->buffer = std::vector<BYTE>(size);
	std::fill_n(&buffer.front(), size, 192);
#ifdef DEBUG
#define DOT_SPACE 10
	for (size_t i = 0; i < width - 1; i += DOT_SPACE) {
		for (size_t j = 0; j < height - 1; j += DOT_SPACE) {
			this->set(i, j, 0, 0, 0);
		}
	}
#endif
}

std::vector<BYTE> close::RgbBuffer::get() {
	return buffer;
}

void close::RgbBuffer::set(size_t x, size_t y, BYTE R, BYTE G, BYTE B) {
	buffer.at(x * RGB_CHANNEL_COUNT + y * this->width * RGB_CHANNEL_COUNT) = R;
	buffer.at(x * RGB_CHANNEL_COUNT + y * this->width * RGB_CHANNEL_COUNT + 1) = G;
	buffer.at(x * RGB_CHANNEL_COUNT + y * this->width * RGB_CHANNEL_COUNT + 2) = B;
}

size_t close::RgbBuffer::getWidth() {
	return width;
}

size_t close::RgbBuffer::getHeight() {
	return height;
}
