#pragma once
#include <tuple>
#include "../../../services.hpp"
#include "../../../camera/camera.hpp"

namespace close {

	class RgbBuffer {
	public:
		RgbBuffer(size_t width, size_t height);
		std::vector<BYTE> get();
		void set(size_t x, size_t y, BYTE R, BYTE G, BYTE B);
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
		BYTE toRGBProp(Slope prop);
	};

	class RasterJob {
	public:
		std::vector<unsigned char> apply(std::vector<data::VertexPayload>*);
		RasterJob();
	private:
		void draw(RgbBuffer* buffer, std::vector<float>* zBuffer, data::VertexPayload* v0, data::VertexPayload* v1, data::VertexPayload* v2);
		std::vector<Slope> createSlope(glm::vec3* p0, glm::vec3* p1, data::VertexPayload* start, data::VertexPayload* end, int steps);
		bool isTheShorterSide(glm::vec3* p0, glm::vec3* p1, glm::vec3* p2);
		glm::vec3 extract(data::VertexPayload* vertex);
		void order(data::VertexPayload* v0, data::VertexPayload* v1, data::VertexPayload* v2, glm::vec3* p0, glm::vec3* p1, glm::vec3* p2);
		Scanner* scanner;
	};


}