#pragma once

#include "vgl.h"
#include "../services/services.hpp"
#include "../services/render/render.hpp"
#include "../data/data.hpp"

class Application {
private:
	GLFWwindow* window;
	ModelFactory* factory;
	OpenGLRenderer* renderer;
public:
	void init();
	void loop();
	void detroy();
	~Application();
};

class KeyCommandStrategy {
protected:
	Camera* camera;
public:
	KeyCommandStrategy();
	virtual bool matches(int key, int action) = 0;
	virtual void apply(float angle) = 0;
};

class PitchUp: public KeyCommandStrategy {
	virtual bool matches(int key, int action);
	virtual void apply(float angle);
};

class PitchDown : public KeyCommandStrategy {
	virtual bool matches(int key, int action);
	virtual void apply(float angle);
};

class YawLeft : public KeyCommandStrategy {
	virtual bool matches(int key, int action);
	virtual void apply(float angle);
};

class YawRight : public KeyCommandStrategy {
	virtual bool matches(int key, int action);
	virtual void apply(float angle);
};

class RollRight : public KeyCommandStrategy {
	virtual bool matches(int key, int action);
	virtual void apply(float angle);
};

class RollLeft : public KeyCommandStrategy {
	virtual bool matches(int key, int action);
	virtual void apply(float angle);
};

class Reset : public KeyCommandStrategy {
	virtual bool matches(int key, int action);
	virtual void apply(float angle);
};

class RotateLeft : public KeyCommandStrategy {
	virtual bool matches(int key, int action);
	virtual void apply(float angle);
};

class RotateRight : public KeyCommandStrategy {
	virtual bool matches(int key, int action);
	virtual void apply(float angle);
};

class MoveLeft : public KeyCommandStrategy {
	virtual bool matches(int key, int action);
	virtual void apply(float angle);
};

class MoveRight : public KeyCommandStrategy {
	virtual bool matches(int key, int action);
	virtual void apply(float angle);
};

class MoveFront : public KeyCommandStrategy {
	virtual bool matches(int key, int action);
	virtual void apply(float angle);
};

class MoveBack : public KeyCommandStrategy {
	virtual bool matches(int key, int action);
	virtual void apply(float angle);
};

class KeyStrategyService {
private:
	vector<KeyCommandStrategy*>* strategies;
	static KeyStrategyService* instance;
	KeyStrategyService();
public:
	vector<KeyCommandStrategy*>* getKeyStrategies();
	static KeyStrategyService* getInstance();
};
