#include "raster.h"

using namespace close;

Scanner::Scanner() {

}

void close::Scanner::scanline(RgbBuffer* buffer, int y, std::vector<Slope>* left, std::vector<Slope>* right) {
	int start = left->at(0).get();
	int end = right->at(0).get();

	for (int x = start; x <= end; ++x) {
		auto R = (BYTE)(left->at(1).get() * 255.f);
		auto G = (BYTE)(left->at(2).get() * 255.f);
		auto B = (BYTE)(left->at(3).get() * 255.f);
		buffer->set(x, y, R, G, B);
	}
	for (int props = 0; props < left->size(); props++) {
		left->at(props).next();
		right->at(props).next();
	}
}
