#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	void reset(glm::vec2 u, glm::vec2 v, float fov);
	glm::mat4 getView();
	static Camera& getInstance();
private:
	Camera();
	static Camera* instance;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::mat4 view;
};