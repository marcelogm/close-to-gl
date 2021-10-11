#include "raster.h"

using namespace close;

void Scanner::scanline(RgbBuffer* buffer, float* zBuffer, int y, vector<Slope>* left, vector<Slope>* right) {
	const int start = left->at(0).get();
	const int end = right->at(0).get();

	Slope props[PROPS_FOR_INTERPOLATION];
	for (int i = 0; i < PROPS_FOR_INTERPOLATION; ++i) {
		int steps = end - start;
		props[i] = Slope(left->at(i + 1).get(), right->at(i + 1).get(), steps);
	}

	for (int x = start; x < end; x++) {
		int mode = *Config::getInstance()->getRenderMode();
		if ((x == start) || x == end || mode == RENDER_MODE_TRIANGLE){
			this->draw(buffer, zBuffer, x, y, props);
		}
		for (int i = 0; i < 7; ++i) {
			props[i].next();
		}
	}
	for (int i = 0; i < PROPS_SLOPE_COUNT; i++) {
		left->at(i).next();
		right->at(i).next();
	}
}

void Scanner::draw(RgbBuffer* buffer, float* zBuffer, int x, int y, Slope* props) {
	const auto w = 1.0f / props[6].get();
	const auto z = props[5].get() * w;
	const auto zBufferIndex = y * buffer->getWidth() + x;

	if (z > zBuffer[zBufferIndex]) {
		zBuffer[zBufferIndex] = z;
		
		// we must perfom the perspective correct interpolation 
		// after the z-buffer test to save processing power
		const auto colorR = props[0].get() * w;
		const auto colorG = props[1].get() * w;
		const auto colorB = props[2].get() * w;
		const auto texCoordX = props[3].get() * w;
		const auto texCoordY = props[4].get() * w;
		const auto deltaTexCoordX = props[3].getStep() * w;
		const auto deltaTexCoordY = props[4].getStep() * w;

		for (auto &filter : this->filters) {
			if (filter->matches()) {
				const vec3 filtered = filter->apply(&texture, texCoordX, texCoordY, vec3(colorR, colorG, colorB), deltaTexCoordX, deltaTexCoordY);
				buffer->set(x, y, filtered.r, filtered.g, filtered.b);
			}
		}
	}
}

close::Scanner::Scanner() {
	texture = TextureProvider().get();
	config = Config::getInstance();
	filters = vector<FilterStrategy*>();
	filters.push_back(new filter::NoTexture());
	filters.push_back(new filter::NearestNeighborResampling());
	filters.push_back(new filter::BilinearResampling());
	filters.push_back(new filter::MipmapResampling());
}

BYTE close::Scanner::toRGBProp(Slope prop) {
	return (BYTE)(prop.get() * 255.f);
}