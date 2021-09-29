#pragma once
#include "../../../services.hpp"
#include "../../../camera/camera.hpp"

namespace close {

	class RasterJob {
	public:
		std::vector<unsigned char> apply(std::vector<data::VertexPayload>*);
		RasterJob();
	};

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

}