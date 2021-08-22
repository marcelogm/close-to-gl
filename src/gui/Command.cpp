#include "gui.hpp"

KeyCommandStrategy::KeyCommandStrategy() {
	this->camera = Camera::getInstance();
	this->config = Config::getInstance();
}

bool KeyCommandStrategy::isPressing(int action) {
	return (action == GLFW_PRESS || action == GLFW_REPEAT);
}

float KeyCommandStrategy::getSensibility() {
	return (*config->getSensibility() / 100);
}

class SwitchBetweenMovementTypes : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS;
	};

	void apply(float angle) {
		bool* move = config->getMove();
		*move = !*move;
	};
};

class PitchUp : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_UP && isPressing(action) && *config->getMove();
	};

	void apply(float angle) {
		camera->look(0.0f, 10.0f * getSensibility());
	};
};

class PitchDown : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_DOWN && isPressing(action) && *config->getMove();
	};

	void apply(float angle) {
		camera->look(0.0f, -10.0f * getSensibility());
	};
};

class YawLeft : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return  key == GLFW_KEY_LEFT && isPressing(action) &&*config->getMove();
	};

	void apply(float angle) {
		camera->look(-10.0f * getSensibility(), 0.0f);
	};
};

class YawRight : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return  key == GLFW_KEY_RIGHT && isPressing(action) &&*config->getMove();
	};

	void apply(float angle) {
		camera->look(10.0f * getSensibility(), 0.0f);
	};
};

class RollRight : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_Z && isPressing(action) && *config->getMove();
	};

	void apply(float angle) {
		camera->roll(10.0f * getSensibility());
	};
};

class RollLeft : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_X && isPressing(action) && *config->getMove();
	};

	void apply(float angle) {
		camera->roll(-10.0f * getSensibility());
	};
};

class MoveLeft : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_LEFT && isPressing(action) && !*config->getMove();
	};

	void apply(float angle) {
		camera->goLeft(100.0f * getSensibility());
	};
};

class MoveRight : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return  key == GLFW_KEY_RIGHT && isPressing(action) && !*config->getMove();
	};

	void apply(float angle) {
		camera->goRight(100.0f * getSensibility());
	};
};

class MoveFront : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return  key == GLFW_KEY_UP && isPressing(action) && !*config->getMove();
	};

	void apply(float angle) {
		camera->goFoward(100.0f * getSensibility());
	};
};

class MoveBack : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_DOWN && isPressing(action) && !*config->getMove();
	};

	void apply(float angle) {
		camera->goBack(100.0f * getSensibility());
	};
};

class MoveUp : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_Z && isPressing(action) && !*config->getMove();
	};

	void apply(float angle) {
		camera->goUp(100.0f * getSensibility());
	};
};

class MoveDown : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_X && isPressing(action) && !*config->getMove();
	};

	void apply(float angle) {
		camera->goDown(100.0f * getSensibility());
	};
};

KeyStrategyService::KeyStrategyService() {
	strategies = new std::vector<KeyCommandStrategy*>();
	strategies->push_back(new PitchUp());
	strategies->push_back(new PitchDown());
	strategies->push_back(new RollLeft());
	strategies->push_back(new RollRight());
	strategies->push_back(new YawLeft());
	strategies->push_back(new YawRight());
	strategies->push_back(new MoveFront());
	strategies->push_back(new MoveBack());
	strategies->push_back(new MoveRight());
	strategies->push_back(new MoveLeft());
	strategies->push_back(new MoveUp());
	strategies->push_back(new MoveDown());
	strategies->push_back(new SwitchBetweenMovementTypes());
}

std::vector<KeyCommandStrategy*>* KeyStrategyService::getKeyStrategies() {
	return strategies;
}

KeyStrategyService* KeyStrategyService::getInstance() {
	if (instance == nullptr) {
		instance = new KeyStrategyService();
	}
	return instance;
}

KeyStrategyService* KeyStrategyService::instance = nullptr;