#include "raster.h"

using namespace close;

Scanner::Scanner() {

}

void close::Scanner::scanline(RgbBuffer* buffer, std::vector<float>* zBuffer, int x, std::vector<Slope>* left, std::vector<Slope>* right) {
	int start = left->at(0).get();
	int end = right->at(0).get();

	std::vector<Slope> props(4);
	for (int i = 0; i < 4; ++i) {
		int steps = end - start;
		props.at(i) = Slope(left->at(i + 1).get(), right->at(i + 1).get(), steps);
	}

	for (int y = start; y <= end; ++y) {
		int mode = *Config::getInstance()->getRenderMode();
		if (y == start || y == end || mode == RENDER_MODE_TRIANGLE){
			this->draw(buffer, zBuffer, x, y, &props);
		}
		for (int i = 0; i < 4; ++i) {
			props.at(i).next();
		}
	}
	for (int i = 0; i < left->size(); i++) {
		left->at(i).next();
		right->at(i).next();
	}
}

void close::Scanner::draw(RgbBuffer* buffer, std::vector<float>* zBuffer, int x, int y, std::vector<Slope>* props) {
	auto z = 1.f / props->at(3).get();
	auto zBufferIndex = x * buffer->getHeight() + y;
	if (z < zBuffer->at(zBufferIndex)) {
		zBuffer->at(zBufferIndex) = z;
		auto R = this->toRGBProp(props->at(0)) * z;
		auto G = this->toRGBProp(props->at(1)) * z;
		auto B = this->toRGBProp(props->at(2)) * z;
		buffer->set(x, y, R, G, B);
	}
}

BYTE close::Scanner::toRGBProp(Slope prop) {
	return (BYTE)(prop.get() * 255.f);
}