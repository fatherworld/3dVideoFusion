//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "Camera.h"
//#include "Shader.h"
//#include "Model.h"
//
//#include <iostream>
//#include <direct.h>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//std::string getFullPath(std::string path);
//
//const unsigned int SCR_WIDTH = 1280;
//const unsigned int SCR_HEIGHT = 720;
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//int main() {
//
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif
//
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL) {
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	glEnable(GL_DEPTH_TEST);
//
//	Shader ourShader("ShaderSource\\shader.vs", "ShaderSource\\shader.fs");
//	Shader ourShader1("ShaderSource\\shader.vs", "ShaderSource\\shader.fs");
//
//
//	Model ourModel1(getFullPath("nanosuit\\nanosuit.obj").c_str());
//
//	Model ourModel(getFullPath("zuanyuan\\5352757_farm.obj").c_str());
//
//
//	while (!glfwWindowShouldClose(window)) {
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		processInput(window);
//
//		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		ourShader1.use();
//		ourShader.use();
//
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		ourShader.setMat4("projection", glm::value_ptr(projection));
//		ourShader.setMat4("view", glm::value_ptr(view));
//		ourShader1.setMat4("projection", glm::value_ptr(projection));
//		ourShader1.setMat4("view", glm::value_ptr(view));
//
//		glm::mat4 model, mode2;
//		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
//		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
//
//		mode2 = glm::translate(model, glm::vec3(0.0f, -2.5f, 0.0f));
//		mode2 = glm::scale(mode2, glm::vec3(0.2f, 0.2f, 0.2f));
//		ourShader.setMat4("model", glm::value_ptr(model));
//
//		ourShader1.setMat4("model", glm::value_ptr(mode2));
//
//		
//
//		ourModel.Draw(ourShader);
//		ourModel1.Draw(ourShader1);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}
//
//void processInput(GLFWwindow *window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//
//void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
//	if (firstMouse) {
//		lastX = xPos;
//		lastY = yPos;
//		firstMouse = false;
//	}
//
//	float xoffset = lastX - xPos;	//别忘了，在窗口中，左边的坐标小于右边的坐标，而我们需要一个正的角度
//	float yoffset = lastY - yPos;	//同样，在窗口中，下面的坐标大于上面的坐标，而我们往上抬头的时候需要一个正的角度
//	lastX = xPos;
//	lastY = yPos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
//	camera.ProcessMouseScroll(yoffset);
//}
//
//std::string getFullPath(std::string path) {
//	char* buffer;
//	buffer = _getcwd(NULL, 0);
//	std::string fullPath(buffer);
//
//	fullPath = fullPath + "\\" + path;
//
//	return fullPath;
//}