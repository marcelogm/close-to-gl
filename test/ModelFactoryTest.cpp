#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <services/services.hpp>
#include <data/data.hpp>
#include <iostream>
#include <stdexcept>

using namespace std;

void assertColor(data::RGBColor* color, data::RGBColor* expected) {
	ASSERT_EQ(color->r, expected->r);
	ASSERT_EQ(color->g, expected->g);
	ASSERT_EQ(color->b, expected->b);
}

TEST(ModelFactoryTest, ShouldNotBreakIfFileExists) {
	// given
	unique_ptr<ModelFactory> provider(new ModelFactory());

	// when
	auto model = provider->get("data/square.mock");

	// then
	ASSERT_NO_FATAL_FAILURE();
}


TEST(ModelFactoryTest, ShouldBreakIfFileDoesntExists) {
	// given
	unique_ptr<ModelFactory> provider(new ModelFactory());

	// expect
	ASSERT_THROW(provider->get("data/other.mock"), runtime_error);
}


TEST(ModelFactoryTest, ShouldGetObjectName) {
	// given
	unique_ptr<ModelFactory> provider(new ModelFactory());

	// when
	auto model = make_unique<data::Model>(*provider->get("data/square.mock"));

	// then
	ASSERT_EQ(*model->getName(), "SQUARE");
}


TEST(ModelFactoryTest, ShouldGetObjectMaterials) {
	// given
	unique_ptr<ModelFactory> provider(new ModelFactory());

	// when
	auto model = make_unique<data::Model>(*provider->get("data/square.mock"));

	// then
	ASSERT_EQ(model->getMaterials()->size(), 1);
	auto material = model->getMaterials()->at(0);
	ASSERT_EQ(*material->getAmbientColor(), glm::vec3(0.694, 0.580, 0.459));
	ASSERT_EQ(*material->getDiffuseColor(), glm::vec3(0.992, 0.941, 0.863));
	ASSERT_EQ(*material->getSpecularColor(), glm::vec3(1.000, 1.000, 1.000));
	ASSERT_EQ(material->getShineCoeff(), 0.250);
}


TEST(ModelFactoryTest, ShouldGetTrianglesFromFile) {
	// given
	unique_ptr<ModelFactory> provider(new ModelFactory());

	// when
	auto model = make_unique<data::Model>(*provider->get("data/square.mock"));

	// then
	auto triangles = model->getTriangles();
	auto t0 = triangles->at(0);
	ASSERT_EQ(*t0->getFaceNormal(), glm::vec3(0.0, 0.0, 1.0));

	auto t0v0 = t0->getVertices()->at(0);
	ASSERT_EQ(*t0v0->getPosition(), glm::vec3(-1.0, -1.0, -2.0));
	ASSERT_EQ(*t0v0->getNormal(), glm::vec3(0.0, 0.0, 1.0));
	ASSERT_EQ(t0v0->getColorIndex(), 0);

	auto t0v1 = t0->getVertices()->at(1);
	ASSERT_EQ(*t0v1->getPosition(), glm::vec3(1.0, -1.0, -2.0));
	ASSERT_EQ(*t0v1->getNormal(), glm::vec3(0.0, 0.0, 1.0));
	ASSERT_EQ(t0v1->getColorIndex(), 0);

	auto t0v2 = t0->getVertices()->at(2);
	ASSERT_EQ(*t0v2->getPosition(), glm::vec3(1.0, 1.0, -2.0));
	ASSERT_EQ(*t0v2->getNormal(), glm::vec3(0.0, 0.0, 1.0));
	ASSERT_EQ(t0v2->getColorIndex(), 0);

	// and
	auto t1 = triangles->at(1);
	ASSERT_EQ(*t1->getFaceNormal(), glm::vec3(0.0, 0.0, 1.0));

	auto t1v0 = t1->getVertices()->at(0);
	ASSERT_EQ(*t1v0->getPosition(), glm::vec3(1.0, 1.0, -2.0));
	ASSERT_EQ(*t1v0->getNormal(), glm::vec3(0.0, 0.0, 1.0));
	ASSERT_EQ(t1v0->getColorIndex(), 0);

	auto t1v1 = t1->getVertices()->at(1);
	ASSERT_EQ(*t1v1->getPosition(), glm::vec3(-1.0, 1.0, -2.0));
	ASSERT_EQ(*t1v1->getNormal(), glm::vec3(0.0, 0.0, 1.0));
	ASSERT_EQ(t1v1->getColorIndex(), 0);

	auto t1v2 = t1->getVertices()->at(2);
	ASSERT_EQ(*t1v2->getPosition(), glm::vec3(-1.0, -1.0, -2.0));
	ASSERT_EQ(*t1v2->getNormal(), glm::vec3(0.0, 0.0, 1.0));
	ASSERT_EQ(t1v2->getColorIndex(), 0);
}

TEST(ModelFactoryTest, ShouldPreProcessVertexColors) {
	// given
	unique_ptr<data::RGBColor> color(new data::RGBColor({ 252, 239, 220 }));
	unique_ptr<ModelFactory> provider(new ModelFactory());

	// when
	auto model = make_unique<data::Model>(*provider->get("data/square.mock"));

	// then
	auto triangles = model->getTriangles();
	auto t0 = triangles->at(0);
	auto t0v0 = t0->getVertices()->at(0)->getColor();
	assertColor(t0v0, color.get());
	auto t0v1 = t0->getVertices()->at(1)->getColor();
	assertColor(t0v0, color.get());
	auto t0v2 = t0->getVertices()->at(2)->getColor();
	assertColor(t0v0, color.get());

	// and
	auto t1 = triangles->at(1);
	auto t1v0 = t1->getVertices()->at(0)->getColor();
	assertColor(t1v0, color.get());
	auto t1v1 = t1->getVertices()->at(1)->getColor();
	assertColor(t1v1, color.get());
	auto t1v2 = t1->getVertices()->at(2)->getColor();
	assertColor(t1v2, color.get());
}


TEST(ModelFactoryTest, A) {
	// given
	unique_ptr<data::RGBColor> color(new data::RGBColor({ 252, 239, 220 }));
	unique_ptr<ModelFactory> provider(new ModelFactory());
	
	for (int i = 0; i < 10000000; i++) {
		auto ptr = provider->get("data/square.mock");
		delete ptr;
	}
}