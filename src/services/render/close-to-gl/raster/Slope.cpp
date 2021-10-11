#include "raster.h"

using namespace close;

Slope::Slope() {
	this->curent = 0.f;
	this->step = 0.f;
}

close::Slope::Slope(float start, float end, int steps) {
	const float inv = 1.f / steps;
	this->curent = start;
	this->step = (end - start) * inv;
}

float close::Slope::get() {
	return this->curent;
}

float close::Slope::getStep() {
	return this->step;
}

void close::Slope::next() {
	this->curent += step;
}
