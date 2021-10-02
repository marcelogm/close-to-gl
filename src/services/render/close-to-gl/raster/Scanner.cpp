#include "raster.h"

using namespace close;

void Scanner::scanline(RgbBuffer* buffer, float* zBuffer, int x, vector<Slope>* left, vector<Slope>* right) {
	const int start = left->at(0).get();
	const int end = right->at(0).get();

	Slope props[PROPS_FOR_INTERPOLATION];
	for (int i = 0; i < PROPS_FOR_INTERPOLATION; ++i) {
		int steps = end - start;
		props[i] = Slope(left->at(i + 1).get(), right->at(i + 1).get(), steps);
	}

	for (int y = start; y <= end; ++y) {
		int mode = *Config::getInstance()->getRenderMode();
		if (y == start || y == end || mode == RENDER_MODE_TRIANGLE){
			this->draw(buffer, zBuffer, x, y, props);
		}
		for (int i = 0; i < 4; ++i) {
			props[i].next();
		}
	}
	for (int i = 0; i < PROPS_SLOPE_COUNT; i++) {
		left->at(i).next();
		right->at(i).next();
	}
}

void Scanner::draw(RgbBuffer* buffer, float* zBuffer, int x, int y, Slope* props) {
	const auto z = 1.f / props[3].get();
	const auto zBufferIndex = x * buffer->getHeight() + y;
	if (z < zBuffer[zBufferIndex]) {
		zBuffer[zBufferIndex] = z;
		auto R = this->toRGBProp(props[0]) * z;
		auto G = this->toRGBProp(props[1]) * z;
		auto B = this->toRGBProp(props[2]) * z;
		buffer->set(x, y, R, G, B);
	}
}

BYTE close::Scanner::toRGBProp(Slope prop) {
	return (BYTE)(prop.get() * 255.f);
}