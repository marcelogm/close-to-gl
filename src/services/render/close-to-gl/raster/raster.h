#pragma once
#include <tuple>
#include "../../../services.hpp"
#include "../../../camera/camera.hpp"

#define PROPS_SLOPE_COUNT 5
#define PROPS_FOR_INTERPOLATION (PROPS_SLOPE_COUNT - 1)

using std::vector;
using data::VertexPayload;

namespace close {

	class RgbBuffer {
	public:
		RgbBuffer(size_t width, size_t height);
		vector<BYTE> get();
		void set(size_t x, size_t y, BYTE R, BYTE G, BYTE B);
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
		Scanner();
		void scanline(RgbBuffer* buffer, float* zBuffer, int y, vector<Slope>* left, vector<Slope>* right);
		void draw(RgbBuffer* buffer, float* zBuffer, int x, int y, Slope* props);
	private:
		BYTE toRGBProp(Slope prop);
	};

	class RasterJob {
	public:
		RasterJob(VertexPayload* buffer);
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