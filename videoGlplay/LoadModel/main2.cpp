#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <opencv2/core/core.hpp>    

#include <opencv2/highgui/highgui.hpp>   



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Shader.h"
#include "Model.h"
#include "stb_image.h"
#include <iostream>
#include <direct.h>
#include "videogl.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
std::string getFullPath(std::string path);

static const unsigned int SCR_WIDTH = 1280;
static const unsigned int SCR_HEIGHT = 720;
GLFWwindow* window = NULL;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
static float lastX = SCR_WIDTH / 2.0f;
static float lastY = SCR_HEIGHT / 2.0f;
static bool firstMouse = true;

static float deltaTime = 0.0f;
static float lastFrame = 0.0f;
using namespace cv;
//#define LOCAL_VIDEO LOC
std::string const vert_shader_source =
"#version 150\n"

"in vec3 vertex;\n"

"in vec2 texCoord0;\n"

"uniform mat4 mvpMatrix;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"

"out vec2 texCoord;\n"

"void main() {\n"

"	gl_Position = projection* view* model * vec4(vertex, 1.0);\n"

"	texCoord = texCoord0;\n"

"}\n";



std::string const frag_shader_source =

"#version 150\n"

"uniform sampler2D frameTex;\n"

"in vec2 texCoord;\n"

"out vec4 fragColor;\n"

"void main() {\n"

"	fragColor = texture(frameTex, texCoord);\n"

"}\n";



#define BUFFER_OFFSET(i) ((char *)NULL + (i))





// attribute indices

enum {

	VERTICES = 0,

	TEX_COORDS

};



// uniform indices

enum {

	MVP_MATRIX = 0,

	FRAME_TEX

};



// app data structure

typedef struct {
	/*
	AVFormatContext *fmt_ctx;

	int stream_idx;

	AVStream *video_stream;

	AVCodecContext *codec_ctx;

	AVCodec *decoder;

	AVPacket *packet;

	AVFrame *av_frame;

	AVFrame *gl_frame;

	struct SwsContext *conv_ctx;
	*/
	GLfloat frame_width;
	GLfloat frame_height;

	GLuint vao;

	GLuint vert_buf;

	GLuint elem_buf;

	GLuint frame_tex;

	GLuint program;

	GLuint attribs[2];

	GLuint uniforms[2];

} AppData;


void clearAppData(AppData *data) {
	/*
	if (data->av_frame) av_free(data->av_frame);

	if (data->gl_frame) av_free(data->gl_frame);

	if (data->packet) av_free(data->packet);

	if (data->codec_ctx) avcodec_close(data->codec_ctx);

	if (data->fmt_ctx) avformat_free_context(data->fmt_ctx);
	*/
	glDeleteVertexArrays(1, &data->vao);

	glDeleteBuffers(1, &data->vert_buf);

	glDeleteBuffers(1, &data->elem_buf);

	glDeleteTextures(1, &data->frame_tex);

	//	initializeAppData(data);

}



// read a video frame

bool readFrame(AppData *data, VideoCapture capture) {

	Mat frame;
	capture >> frame;

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, data->frame_width,

		data->frame_height, GL_BGR, GL_UNSIGNED_BYTE,

		frame.data);


	return true;

}



bool buildShader(std::string const &shader_source, GLuint &shader, GLenum type) {

	int size = shader_source.length();



	shader = glCreateShader(type);

	char const *c_shader_source = shader_source.c_str();

	glShaderSource(shader, 1, (GLchar const **)&c_shader_source, &size);

	glCompileShader(shader);

	GLint status;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {

		std::cout << "failed to compile shader" << std::endl;

		int length;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		char *log = new char[length];

		glGetShaderInfoLog(shader, length, &length, log);

		std::cout << log << std::endl;

		delete[] log;

		return false;

	}

	return true;

}



// initialize shaders

bool buildProgram(AppData *data) {

	GLuint v_shader, f_shader;

	if (!buildShader(vert_shader_source, v_shader, GL_VERTEX_SHADER)) {

		std::cout << "failed to build vertex shader" << std::endl;

		return false;

	}



	if (!buildShader(frag_shader_source, f_shader, GL_FRAGMENT_SHADER)) {

		std::cout << "failed to build fragment shader" << std::endl;

		return false;

	}



	data->program = glCreateProgram();

	glAttachShader(data->program, v_shader);

	glAttachShader(data->program, f_shader);

	glLinkProgram(data->program);

	GLint status;

	glGetProgramiv(data->program, GL_LINK_STATUS, &status);

	if (status != GL_TRUE) {

		std::cout << "failed to link program" << std::endl;

		int length;

		glGetProgramiv(data->program, GL_INFO_LOG_LENGTH, &length);

		char *log = new char[length];

		glGetShaderInfoLog(data->program, length, &length, log);

		std::cout << log << std::endl;

		delete[] log;

		return false;

	}



	data->uniforms[MVP_MATRIX] = glGetUniformLocation(data->program, "mvpMatrix");

	data->uniforms[FRAME_TEX] = glGetUniformLocation(data->program, "frameTex");



	data->attribs[VERTICES] = glGetAttribLocation(data->program, "vertex");

	data->attribs[TEX_COORDS] = glGetAttribLocation(data->program, "texCoord0");



	return true;

}



// draw frame in opengl context

void drawFrame(AppData *data) {


	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, data->frame_tex);

	glBindVertexArray(data->vao);

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));

	glDrawArrays(GL_TRIANGLES, 0, 36);


	glBindVertexArray(0);

	glfwSwapBuffers(window);

}




int main() {




	AppData dataY;


	// open video

#ifdef LOCAL_VIDEO
	//本地视频流
	const char* filename = "./images/1.mp4";

	VideoCapture capture(filename);


#else
	//摄像头视频流
	VideoCapture capture(0);

#endif
	//打开文件视频流




	// initialize glfw

	if (!glfwInit()) {

		std::cout << "glfw failed to init" << std::endl;

		glfwTerminate();

		clearAppData(&dataY);

		return -1;

	}





	dataY.frame_height = (float)capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	dataY.frame_width = (float)capture.get(CV_CAP_PROP_FRAME_WIDTH);

	// open a window

	float aspect = (float)dataY.frame_width / (float)dataY.frame_height;


	int adj_width = aspect * 1000;

	int adj_height = 1000;


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}




	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);



	// initialize shaders

	if (!buildProgram(&dataY)) {

		std::cout << "failed to initialize shaders" << std::endl;

		glfwTerminate();

		clearAppData(&dataY);

		return -1;

	}

	glUseProgram(dataY.program);



	// initialize renderable

	glGenVertexArrays(1, &dataY.vao);

	glBindVertexArray(dataY.vao);



	glGenBuffers(1, &dataY.vert_buf);

	glBindBuffer(GL_ARRAY_BUFFER, dataY.vert_buf);

	/*
	float quad[20] = {

	-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,

	-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,

	1.0f, -1.0f, 0.0f, 1.0f, 1.0f,

	1.0f,  1.0f, 0.0f, 1.0f, 0.0f

	};
	*/


	/*
	放映一半的纹理
	float quad[20] = {

	-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,

	-1.0f, -1.0f, 0.0f, 0.0f, 0.5f,

	1.0f, -1.0f, 0.0f, 0.5f, 0.5f,

	1.0f,  1.0f, 0.0f, 0.5f, 0.0f

	};
	*/



	/*
	放映GL二维平面模型的一半空间

	float quad[20] = {

	-0.5f,  0.5f, 0.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, 0.0f, 0.0f, 0.5f,

	0.5f, -0.5f, 0.0f, 0.5f, 0.5f,

	0.5f,  0.5f, 0.0f, 0.5f, 0.0f

	};
	*/


	/*
	放映Gl三维平面模型

	float quad[180] =
	{
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f

	};
	*/

	//将视频投放到立方体的1个面上
#ifdef VIDEO_ONE_FACE

	float vertices[] = {
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,

		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f,  0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,

		-1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
		-1.0f, 1.0f, -1.0f,  0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,  0.0f, 0.0f,
		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,

		-1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
		-1.0f, 1.0f, -1.0f, 0.0f, 0.0f
	};
#else

	//将视频投放到立方体的6个面上

	float vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f,0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f,0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};



#endif



	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);




	glVertexAttribPointer(dataY.attribs[VERTICES], 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),

		BUFFER_OFFSET(0));

	glEnableVertexAttribArray(dataY.attribs[VERTICES]);




	glVertexAttribPointer(dataY.attribs[TEX_COORDS], 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),

		BUFFER_OFFSET(12));

	glEnableVertexAttribArray(dataY.attribs[TEX_COORDS]);

	/*

	glGenBuffers(1, &data.elem_buf);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.elem_buf);



	unsigned char elem[6] = {

	0, 1, 2,

	0, 2, 3

	};

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elem), elem, GL_STATIC_DRAW);

	glBindVertexArray(0);

	*/

	stbi_set_flip_vertically_on_load(true);

	glActiveTexture(GL_TEXTURE0);

	glGenTextures(1, &dataY.frame_tex);

	glBindTexture(GL_TEXTURE_2D, dataY.frame_tex);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dataY.frame_width, dataY.frame_height,

		0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glUniform1i(dataY.uniforms[FRAME_TEX], 0);










	glEnable(GL_DEPTH_TEST);

	Shader ourShader("ShaderSource\\shader.vs", "ShaderSource\\shader.fs");



	Model ourModel(getFullPath("nanosuit\\nanosuit.obj").c_str());

	//Model ourModel(getFullPath("zuanyuan\\5352757_farm.obj").c_str());

	bool running = true;
	while (!glfwWindowShouldClose(window) && readFrame(&dataY, capture) && running) {
		

		ourModel.Draw(ourShader);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput(window);



		ourShader.use();

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("projection", glm::value_ptr(projection));
		ourShader.setMat4("view", glm::value_ptr(view));

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		ourShader.setMat4("model", glm::value_ptr(model));

		glfwSwapBuffers(window);
		
		drawFrame(&dataY);

		
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xoffset = lastX - xPos;	//别忘了，在窗口中，左边的坐标小于右边的坐标，而我们需要一个正的角度
	float yoffset = lastY - yPos;	//同样，在窗口中，下面的坐标大于上面的坐标，而我们往上抬头的时候需要一个正的角度
	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}

std::string getFullPath(std::string path) {
	char* buffer;
	buffer = _getcwd(NULL, 0);
	std::string fullPath(buffer);

	fullPath = fullPath + "\\" + path;

	return fullPath;
}