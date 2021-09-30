#pragma once
#include <tuple>
#include "../../../services.hpp"
#include "../../../camera/camera.hpp"

using std::vector;
using data::VertexPayload;

namespace close {

	class RgbBuffer {
	public:
		RgbBuffer(size_t width, size_t height);
		std::vector<BYTE> get();
		void set(size_t x, size_t y, BYTE R, BYTE G, BYTE B);
		size_t getWidth();
		size_t getHeight();
	private:
		size_t width;
		size_t height;
		std::vector<BYTE> buffer;
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
		void scanline(RgbBuffer* buffer, std::vector<float>* zBuffer, int y, std::vector<Slope>* left, std::vector<Slope>* right);
		void draw(RgbBuffer* buffer, std::vector<float>* zBuffer, int x, int y, std::vector<Slope>* props);
		BYTE toRGBProp(Slope prop);
	};

	class RasterJob {
	public:
		std::vector<unsigned char> apply(size_t count);
		RasterJob(vector<VertexPayload>* buffer);
	private:
		void draw(RgbBuffer* buffer, std::vector<float>* zBuffer, data::VertexPayload* v0, data::VertexPayload* v1, data::VertexPayload* v2);
		std::vector<Slope> createSlope(data::VertexPayload* start, data::VertexPayload* end);
		bool isTheShorterSide(glm::vec4* p0, glm::vec4* p1, glm::vec4* p2);
		void floor(data::VertexPayload* vertex);
		void order(data::VertexPayload* v0, data::VertexPayload* v1, data::VertexPayload* v2);
		Scanner* scanner;
		vector<VertexPayload>* buffer;
	};


}