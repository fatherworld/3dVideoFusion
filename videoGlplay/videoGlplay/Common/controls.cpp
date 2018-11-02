

#include "controls.h"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::mat4 ModelMatrix;


glm::mat4 getViewMatrix() {
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}
glm::mat4 getModelMatrix()
{
	return ModelMatrix;
}

// Initial position : on +Z
glm::vec3 position = glm::vec3(0, 0, 5);
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 0.5f; // 3 units / second
float mouseSpeed = 0.005f;
float rotates_y = 0.0f;
float rotates_x = 0.0f;

void computeMatricesFromInputs(glm::mat4 model) {

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	//glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
	verticalAngle += mouseSpeed * float(768 / 2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
		rotates_x =  deltaTime * speed;

		cout << "Move froward rotates is " << rotates_x << endl;

	}
	
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;

		rotates_x = -deltaTime * speed;

		cout << "Move backward rotates is " << rotates_x << endl;
	}
	
	if (!glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		rotates_x = 0;
		
	}

	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += right * deltaTime * speed;

		rotates_y = deltaTime * speed;


		cout << "Strafe right  " << rotates_y<< endl;

	}
	
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
		rotates_y = -deltaTime * speed;
		cout << "Strafe left " << rotates_y << endl;
	}

	if (!glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && !glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		rotates_y = 0;

	}
	
	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

						   // Projection matrix : 45?Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);

	//cout << "current position is " << endl;
	//cout << "X_coordinate" << position.x <<"Y_coordinate"<<position.y<< "Z_coordinate"<< position.z << endl;
	//cout << " current rotates is " << rotates << endl;

	ModelMatrix = glm::rotate(model, rotates_y * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));//绕y轴进行旋转
	
	ModelMatrix = glm::rotate(ModelMatrix, rotates_x * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));//绕x轴进行旋转

	model = ModelMatrix;

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}