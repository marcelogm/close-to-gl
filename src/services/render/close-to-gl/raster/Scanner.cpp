#include "raster.h"

using namespace close;

Scanner::Scanner() {

}

void close::Scanner::scanline(RgbBuffer* buffer, int y, std::vector<Slope>* left, std::vector<Slope>* right) {
	int start = left->at(0).get();
	int end = right->at(0).get();
	
	std::vector<Slope> props(3);
	for (int i = 0; i < 3; ++i) {
		int steps = end - start;
		props.at(i) = Slope(left->at(i + 1).get(), right->at(i + 1).get(), steps);
	}

	for (int x = start; x <= end; ++x) {
		auto R = this->toRGBProp(props.at(0));
		auto G = this->toRGBProp(props.at(1));
		auto B = this->toRGBProp(props.at(2));
		buffer->set(x, y, R, G, B);

		for (int i = 0; i < 3; ++i) {
			props.at(i).next();
		}
	}
	for (int i = 0; i < left->size(); i++) {
		left->at(i).next();
		right->at(i).next();
	}
}

BYTE close::Scanner::toRGBProp(Slope prop) {
	return (BYTE)(prop.get() * 255.f);
}