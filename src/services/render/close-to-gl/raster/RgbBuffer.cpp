#include "raster.h"

using namespace close;

RgbBuffer::RgbBuffer(size_t width, size_t height) {
	this->width = width;
	this->height = height;
	const auto size = width * height * 3;
	this->buffer = std::vector<BYTE>(size);
	std::fill_n(&buffer.front(), size, 192);
}

std::vector<BYTE> close::RgbBuffer::get() {
	return buffer;
}

void close::RgbBuffer::set(size_t x, size_t y, BYTE R, BYTE G, BYTE B) {
	buffer.at(x * this->width * 3 + y * 3) = R;
	buffer.at(x * this->width * 3 + y * 3 + 1) = G;
	buffer.at(x * this->width * 3 + y * 3 + 2) = B;
}
