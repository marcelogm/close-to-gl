#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>

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

	struct VertexData2D {
		float position[2];
		unsigned char color[3];
	};

	struct VertexDataRange {
		glm::vec2 x;
		glm::vec2 y;
		glm::vec2 z;
	};

	class Vertex {
	public:
		Vertex(const Vertex&);
		Vertex::Vertex(glm::vec3*, glm::vec3*, int);
		void setColor(RGBColor* color);
		glm::vec3* getPosition();
		glm::vec3* getNormal();
		int getColorIndex();
		RGBColor* getColor();
		~Vertex();
	private:
		glm::vec3* position;
		glm::vec3* normal;
		int colorIndex;
		RGBColor* color;
	};

	class Triangle {
	public:
		Triangle(const Triangle&);
		Triangle::Triangle(std::vector<Vertex*>*, glm::vec3*);
		std::vector<Vertex*>* getVertices();
		glm::vec3* getFaceNormal();
		~Triangle();
	private:
		std::vector<Vertex*>* vertices;
		glm::vec3* faceNormal;
	};

	class Material {
	public:
		Material(const Material&);
		Material(glm::vec3*, glm::vec3*, glm::vec3*, float);
		glm::vec3* getAmbientColor();
		glm::vec3* getDiffuseColor();
		glm::vec3* getSpecularColor();
		float getShineCoeff();
		~Material();
	private:
		glm::vec3* ambientColor;
		glm::vec3* diffuseColor;
		glm::vec3* specularColor;
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