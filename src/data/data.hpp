#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>

using glm::vec2;
using glm::vec3;
using glm::vec4;

namespace data {

	struct RGBColor {
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

	struct VertexData {
		float position[3];
		float normal[3];
		unsigned char color[3];
	};

	struct VertexPayload {
		vec4 position;
		vec3 normal;
		vec3 color;
	};

	struct VertexDataRange {
		vec2 x;
		vec2 y;
		vec2 z;
	};

	class Vertex {
	public:
		Vertex(const Vertex&);
		Vertex::Vertex(vec3*, vec3*, int);
		void setColor(RGBColor* color);
		vec3* getPosition();
		vec3* getNormal();
		int getColorIndex();
		RGBColor* getColor();
		~Vertex();
	private:
		vec3* position;
		vec3* normal;
		int colorIndex;
		RGBColor* color;
	};

	class Triangle {
	public:
		Triangle(const Triangle&);
		Triangle::Triangle(std::vector<Vertex*>*, vec3*);
		std::vector<Vertex*>* getVertices();
		vec3* getFaceNormal();
		~Triangle();
	private:
		std::vector<Vertex*>* vertices;
		vec3* faceNormal;
	};

	class Material {
	public:
		Material(const Material&);
		Material(vec3*, vec3*, vec3*, float);
		vec3* getAmbientColor();
		vec3* getDiffuseColor();
		vec3* getSpecularColor();
		float getShineCoeff();
		~Material();
	private:
		vec3* ambientColor;
		vec3* diffuseColor;
		vec3* specularColor;
		float shineCoeff;
	};

	class Model {
	public:
		Model(const Model&);
		Model(std::string*, std::vector<Triangle*>*, std::vector<Material*>*);
		std::string* getName();
		std::vector<Material*>* getMaterials();
		std::vector<Triangle*>* getTriangles();
		~Model();
	private:
		std::string* name;
		std::vector<Material*>* materials;
		std::vector<Triangle*>* triangles;
	};

}