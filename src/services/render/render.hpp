#pragma once

#include "../../services/services.hpp"
#include "../camera/camera.hpp"
#include "../../data/data.hpp"

#include <vgl.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <LoadShaders.h>


namespace renderer {

	class Renderer {
	public:
		virtual void init(data::Model*) = 0;
		virtual void display() = 0;
		virtual bool test() = 0;
	};

	class OpenGLDrawProcessor {
	public:
		void process(size_t);
		OpenGLDrawProcessor();
	private:
		Config* config;
	};

	class CameraResetProcessor {
	public:
		void process(data::VertexDataRange);
		CameraResetProcessor();
	private:
		Camera* camera;
	};

	class BackgroundProcessor {
	public:
		void process();
	};
}

