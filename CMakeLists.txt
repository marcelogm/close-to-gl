cmake_minimum_required (VERSION 3.8)

project (close-to-gl)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "/MD /O2 /Ob2 /DNDEBUG /mavx2")

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/build)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(RUN_DIR ${PROJECT_SOURCE_DIR}/out/build)

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
	string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/out/build)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib)
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

find_package(OpenGL REQUIRED)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

set(COMMON_LIBS close-to-gl ${OPENGL_LIBRARIES} glfw glm)
set(COMMON_HEADERS include/vgl.h)
set(COMMON_HEADERS include/stb_image.h)
set(IMGUI_SOURCE_DIR lib/imgui)

add_library(close-to-gl
			lib/gl3w.c
			lib/LoadShaders.cpp
			${IMGUI_SOURCE_DIR}/imgui.cpp
			${IMGUI_SOURCE_DIR}/imgui_demo.cpp 
			${IMGUI_SOURCE_DIR}/imgui_draw.cpp 
			${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
			${IMGUI_SOURCE_DIR}/imgui_tables.cpp
			${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
			${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
			"src/gui/Application.cpp" 
			"src/gui/Command.cpp" 
			"src/gui/ImGuiWrapper.cpp" 
			"src/data/Model.cpp" 
			"src/data/Vertex.cpp" 
			"src/data/Triangle.cpp" 
			"src/data/Material.cpp" 
			"src/services/Config.cpp"
			"src/services/ModelFactory.cpp"
			"src/services/render/open-gl/OpenGLRenderer.cpp" 
			"src/services/render/close-to-gl/CloseToGLRenderer.cpp"
			"src/services/camera/Camera.cpp"  
			"src/services/ModelToVertex.cpp" 
			"src/services/render/close-to-gl/CloseToGLPipeline.cpp"
			"src/services/render/close-to-gl/VertexShader.cpp" 
			"src/services/render/close-to-gl/FaceCulling.cpp" 
			"src/services/render/close-to-gl/PerspectiveAndViewport.cpp" 
			"src/services/render/close-to-gl/IlluminationModel.cpp" 
			"src/services/render/ProjectionFromConfig.cpp" 
			"src/services/Debug.cpp" 
			"src/services/render/CameraResetProcessor.cpp" 
			"src/services/render/open-gl/RenderModeProcessor.cpp" 
			"src/services/render/BackgroundProcessor.cpp" 
			"src/services/render/open-gl/LightProcessor.cpp" 
			"src/services/render/close-to-gl/raster/Rasterizer.cpp" 
			"src/services/render/close-to-gl/raster/RgbBuffer.cpp" 
			"src/services/render/close-to-gl/raster/Slope.cpp" 
			"src/services/render/close-to-gl/raster/Scanner.cpp" "src/services/render/open-gl/FilteringProcessor.cpp" "src/services/TextureProvider.cpp")

find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_executable(main WIN32 src/main.cpp ${COMMON_HEADERS} "src/services/render/open-gl/FilteringProcessor.cpp" "src/services/TextureProvider.cpp")
target_link_libraries(main ${COMMON_LIBS})

include_directories(include)
include_directories(lib/glfw/include)
include_directories(lib/glm)
include_directories(lib/imgui)
