#include "raster.h"

using namespace close;

Scanner::Scanner() {

}

void close::Scanner::scanline(RgbBuffer* buffer, int y, Slope* left, Slope* right) {
	int end = right->get();
	for (int i = left->get(); i <= end; ++i) {
		buffer->set(i, y, 0, 0, 0);
	}
	left->next();
	right->next();
}
