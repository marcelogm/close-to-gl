#include "render.hpp"

using namespace renderer;

void BackgroundProcessor::process() {
	glFlush();
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
