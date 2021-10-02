#include "open.hpp"

using namespace open;

void OpenGLDrawProcessor::process(size_t vertices) {
	switch (*config->getRenderMode()) {
	case 0:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, vertices);
		break;
	case 1:
		glDrawArrays(GL_POINTS, 0, vertices);
		break;
	case 2:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, vertices);
		break;
	}
}

OpenGLDrawProcessor::OpenGLDrawProcessor() {
	config = Config::getInstance();
}
