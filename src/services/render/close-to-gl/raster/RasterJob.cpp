#include "raster.h"

using namespace close;


std::vector<unsigned char> close::RasterJob::apply(std::vector<data::VertexPayload>*)
{
	auto config = Config::getInstance();
	return RgbBuffer(*config->getWindowWidth(), *config->getWindowWidth()).get();
}

RasterJob::RasterJob() {

}

