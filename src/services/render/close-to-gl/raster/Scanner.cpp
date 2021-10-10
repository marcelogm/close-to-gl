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

	for (int x = start; x <= end; ++x) {
		int mode = *Config::getInstance()->getRenderMode();
		if (x == start || x == end || mode == RENDER_MODE_TRIANGLE){
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
		auto colorR = props[0].get() * w;
		auto colorG = props[1].get() * w;
		auto colorB = props[2].get() * w;
		auto X1 = props[3].get() * w;
		auto Y1 = props[4].get() * w;
		int textureX = std::ceil((texture.width - 1) * X1);
		int textureY = std::ceil((texture.height - 1) * Y1);

		BYTE R = 0, G = 0, B = 0;
		if (*config->getTextureUse() == 1) {
			R = texture.data[(textureY * texture.width * 3) + (textureX * 3)] * colorR;
			G = texture.data[(textureY * texture.width * 3) + (textureX * 3) + 1] * colorG;
			B = texture.data[(textureY * texture.width * 3) + (textureX * 3) + 2] * colorB;
		} else {
			R = colorR * 255.f;
			G = colorG * 255.f;
			B = colorB * 255.f;
		}
		buffer->set(x, y, R, G, B);
	}
}

close::Scanner::Scanner() {
	texture = TextureProvider().get();
	config = Config::getInstance();
}

BYTE close::Scanner::toRGBProp(Slope prop) {
	return (BYTE)(prop.get() * 255.f);
}