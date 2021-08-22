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

	void apply() {
		bool* move = config->getMove();
		*move = !*move;
	};
};


class SwitchBetweenMouseStatus : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_SPACE && action == GLFW_PRESS;
	};

	void apply() {
		bool* status = config->getMouseStatus();
		*status = !*status;
	};
};


class PitchUp : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_UP && isPressing(action) && *config->getMove();
	};

	void apply() {
		camera->look(0.0f, 10.0f * getSensibility());
	};
};

class PitchDown : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_DOWN && isPressing(action) && *config->getMove();
	};

	void apply() {
		camera->look(0.0f, -10.0f * getSensibility());
	};
};

class YawLeft : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return  key == GLFW_KEY_LEFT && isPressing(action) &&*config->getMove();
	};

	void apply() {
		camera->look(-10.0f * getSensibility(), 0.0f);
	};
};

class YawRight : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return  key == GLFW_KEY_RIGHT && isPressing(action) &&*config->getMove();
	};

	void apply() {
		camera->look(10.0f * getSensibility(), 0.0f);
	};
};

class RollRight : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_Z && isPressing(action) && *config->getMove();
	};

	void apply() {
		camera->roll(10.0f * getSensibility());
	};
};

class RollLeft : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_X && isPressing(action) && *config->getMove();
	};

	void apply() {
		camera->roll(-10.0f * getSensibility());
	};
};

class MoveLeft : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_LEFT && isPressing(action) && !*config->getMove();
	};

	void apply() {
		camera->goLeft(100.0f * getSensibility());
	};
};

class MoveRight : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return  key == GLFW_KEY_RIGHT && isPressing(action) && !*config->getMove();
	};

	void apply() {
		camera->goRight(100.0f * getSensibility());
	};
};

class MoveFront : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return  key == GLFW_KEY_UP && isPressing(action) && !*config->getMove();
	};

	void apply() {
		camera->goFoward(100.0f * getSensibility());
	};
};

class MoveBack : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_DOWN && isPressing(action) && !*config->getMove();
	};

	void apply() {
		camera->goBack(100.0f * getSensibility());
	};
};

class MoveUp : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_Z && isPressing(action) && !*config->getMove();
	};

	void apply() {
		camera->goUp(100.0f * getSensibility());
	};
};

class MoveDown : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_X && isPressing(action) && !*config->getMove();
	};

	void apply() {
		camera->goDown(100.0f * getSensibility());
	};
};

class RotateAroundLeft : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_A && isPressing(action);
	};

	void apply() {
		camera->rotateAround(-10.0f * getSensibility());
	};
};

class RotateAroundRight : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_D && isPressing(action);
	};

	void apply() {
		camera->rotateAround(10.0f * getSensibility());
	};
};

class ResetCamera : public KeyCommandStrategy {
	bool matches(int key, int action) {
		return key == GLFW_KEY_R && action == GLFW_PRESS;
	};

	void apply() {
		camera->requestReset();
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
	strategies->push_back(new SwitchBetweenMouseStatus());
	strategies->push_back(new RotateAroundLeft());
	strategies->push_back(new RotateAroundRight());
	strategies->push_back(new ResetCamera());
}

void KeyStrategyService::apply(int key, int action) {
	for (auto strategy : *this->strategies) {
		if (strategy->matches(key, action)) {
			strategy->apply();
		}
	}
}

KeyStrategyService* KeyStrategyService::getInstance() {
	if (instance == nullptr) {
		instance = new KeyStrategyService();
	}
	return instance;
}

KeyStrategyService* KeyStrategyService::instance = nullptr;

MouseService::MouseService() {
	this->camera = Camera::getInstance();
	this->config = Config::getInstance();
}

void MouseService::apply(double x, double y) {
	if (first) {
		lastX = x;
		lastY = y;
		first = false;
	}
	float xoffset = x - lastX;
	float yoffset = lastY - y;
	lastX = x;
	lastY = y;
	float sensibility = *config->getMouseSensibility() / 100;
	camera->look(xoffset * sensibility, yoffset * sensibility);
}

void MouseService::mouseLeft() {
	first = true;
}

MouseService* MouseService::getInstance() {
	if (instance == nullptr) {
		instance = new MouseService();
	}
	return instance;
}

MouseService* MouseService::instance = nullptr;