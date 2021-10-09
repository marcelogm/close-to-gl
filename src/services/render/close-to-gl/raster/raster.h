#pragma once
#include <tuple>
#include "../../../services.hpp"
#include "../../../camera/camera.hpp"

#define PROPS_SLOPE_COUNT 8
#define PROPS_FOR_INTERPOLATION (PROPS_SLOPE_COUNT - 1)

using std::vector;
using data::VertexPayload;

namespace close {

	class RgbBuffer {
	public:
		RgbBuffer(size_t, size_t);
		vector<BYTE> get();
		void set(size_t, size_t, BYTE, BYTE, BYTE);
		size_t getWidth();
		size_t getHeight();
	private:
		size_t width;
		size_t height;
		vector<BYTE> buffer;
	};

	class Slope {
	public:
		Slope();
		Slope(float, float, int);
		float get();
		void next();
	private:
		float curent;
		float step;
	};

	class Scanner {
	public:
		void scanline(RgbBuffer*, float*, int, vector<Slope>*, vector<Slope>*);
		void draw(RgbBuffer*, float*, int, int, Slope*);
		Scanner();
	private:
		data::Texture texture;
		BYTE toRGBProp(Slope prop);
	};

	class Rasterizer {
	public:
		Rasterizer(VertexPayload* buffer);
		vector<unsigned char> apply(size_t count);
	private:
		void draw(RgbBuffer* buffer, float* zBuffer, VertexPayload* v0, VertexPayload* v1, VertexPayload* v2);
		vector<Slope> createSlope(VertexPayload* start, VertexPayload* end);
		bool isTheShorterSide(glm::vec4* p0, glm::vec4* p1, glm::vec4* p2);
		void floor(VertexPayload* vertex);
		void order(VertexPayload* v0, VertexPayload* v1, VertexPayload* v2);
		Scanner* scanner;
		VertexPayload* buffer;
		Config* config;
	};


}