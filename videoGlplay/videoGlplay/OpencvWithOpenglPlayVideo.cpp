//
//#include <opencv2/core/core.hpp>    
//
//#include <opencv2/highgui/highgui.hpp>    
//
//
//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include<GLFW/glfw3native.h>
//#include <glm/glm.hpp>
////#include <GL/freeglut.h>
//
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <thread>
//#include <windows.h>
//#include <process.h>
//#include <iostream>
//#include "Shader.h"
//#include "controls.h"
//static HANDLE g_Mutex;
//
//using namespace std;
//using namespace cv;
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#define LOCAL_VIDEO LOC
//
////#define VIDEO_ONE_FACE YS
//#define NOTMVPSHADER Y
////#define LOCAL_VIDEO YS
//extern "C"
//{
//#include "libswscale/swscale.h" 
//	//编码
//#include "libavcodec/avcodec.h"
//	//封装格式处理
//#include "libavformat/avformat.h"
//	//像素处理
//#include "libswscale/swscale.h"
//};
//
//int curFrame = 0;
//char imgPath[20] = { 0 };
//#pragma warning(disable:4996)
//
//
//
//static char msg[128] = { 0 };
//GLFWwindow* window = NULL;
//GLint width, height;
//GLfloat ratioY;
//GLfloat xpos, ypos;
//GLfloat fScale = 1.0f;
//GLfloat rquad = 0.0f;
////AppData dataY;
//
////三角形1的顶点着色器代码
//const char* vertexShaderSource1 = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";	//千万别忘记这个\0
//
//
//
////三角形1片元着色器代码
//const char* fragmentShaderSource1 = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\0";	//千万别忘记这个\0
//
//
//static float InnerCube[] =
//{
//	-0.1f, -0.1f, 0.8f,
//	0.1f, -0.1f,  0.8f,
//	0.1f, 0.1f, 0.8f,
//	0.1f, 0.1f,  0.8f,
//	-0.1f, 0.1f,  0.8f,
//	-0.1f, -0.1f, 0.8f,
//
//	-0.1f, -0.1f,1.0f,
//	0.1f, -0.1f,1.0f,
//	0.1f, 0.1f,1.0f,
//	0.1f, 0.1f,1.0f,
//	-0.1f, 0.1f,1.0f,
//	-0.1f, -0.1f,1.0f,
//	-0.1f, 0.1f,1.0f,
//	-0.1f, 0.1f, 0.8f,
//	-0.1f, -0.1f,0.8f,
//	-0.1f, -0.1f, 0.8f,
//	-0.1f, -0.1f,1.0f,
//	-0.1f, 0.1f, 1.0f,
//	0.1f, 0.1f, 1.0f,
//	0.1f, 0.1f, 0.8f,
//	0.1f, -0.1f,0.8f,
//	0.1f, -0.1f,0.8f,
//	0.1f, -0.1f, 1.0f,
//	0.1f, 0.1f,1.0f,
//	-0.1f, -0.1f,0.8f,
//	0.1f, -0.1f,0.8f,
//	0.1f, -0.1f, 1.0f,
//	0.1f, -0.1f,1.0f,
//	-0.1f, -0.1f, 0.8f,
//	-0.1f, -0.1f, 0.8f,
//	-0.1f, 0.1f, 0.8f,
//	0.1f, 0.1f, 0.8f,
//	0.1f, 0.1f,1.0f,
//	0.1f, 0.1f, 1.0f,
//	-0.1f, 0.1f, 1.0f, 
//	-0.1f, 0.1f, 0.8f
//
//};
//
//
//
//
//float verticeys[] = {
//	0.5f, 0.5f, 0.0f,		//左
//	0.7f, 0.7f, 0.0f,		//右
//	0.5f, 0.7f, 0.0f		//上
//};
//
//
//float verticeys2[] = {
//	0.3f, 0.3f, 0.0f,		//左
//	0.5f, 0.5f, 0.0f,		//右
//	0.5f, 0.3f, 0.0f		//上
//	
//};
//
//
//
///*
//float verticeys[] = {
//	1.0f, -0.5f, 0.0f,		//左
//	1.5f, -0.5f, 0.0f,		//右
//	1.5f, 0.5f, 0.0f		//上
//};
//*/
//
//std::string const vert_shader_source =
//
//"#version 150\n"
//
//"in vec3 vertex;\n"
//
//"in vec2 texCoord0;\n"
//
//"uniform mat4 mvpMatrix;\n"
//"uniform mat4 model;\n"
//"uniform mat4 view;\n"
//"uniform mat4 projection;\n"
//
//"out vec2 texCoord;\n"
//
//"void main() {\n"
//
//"	gl_Position = projection* view* model * vec4(vertex, 1.0);\n"
//
//"	texCoord = texCoord0;\n"
//
//"}\n";
//
//
//
//std::string const frag_shader_source =
//
//"#version 150\n"
//
//"uniform sampler2D frameTex;\n"
//
//"in vec2 texCoord;\n"
//
//"out vec4 fragColor;\n"
//
//"void main() {\n"
//
//"	fragColor = texture(frameTex, texCoord);\n"
//
//"}\n";
//
//
//
//#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//
//
//
//
//// attribute indices
//
//enum {
//
//	VERTICES = 0,
//
//	TEX_COORDS
//
//};
//
//
//
//// uniform indices
//
//enum {
//
//	MVP_MATRIX = 0,
//
//	FRAME_TEX
//
//};
//
//
//
//// app data structure
//
//typedef struct {
///*
//	AVFormatContext *fmt_ctx;
//
//	int stream_idx;
//
//	AVStream *video_stream;
//
//	AVCodecContext *codec_ctx;
//
//	AVCodec *decoder;
//
//	AVPacket *packet;
//
//	AVFrame *av_frame;
//
//	AVFrame *gl_frame;
//
//	struct SwsContext *conv_ctx;
//	*/
//	GLfloat frame_width;
//	GLfloat frame_height;
//
//	GLuint vao;
//
//	GLuint vert_buf;
//
//	GLuint elem_buf;
//
//	GLuint frame_tex;
//
//	GLuint program;
//
//	GLuint attribs[2];
//
//	GLuint uniforms[2];
//
//	GLuint small_tex;
//
//} AppData;
//
//
//
//// initialize the app data structure
///*
//void initializeAppData(AppData *data) {
//
//	data->fmt_ctx = NULL;
//
//	data->stream_idx = -1;
//
//	data->video_stream = NULL;
//
//	data->codec_ctx = NULL;
//
//	data->decoder = NULL;
//
//	data->av_frame = NULL;
//
//	data->gl_frame = NULL;
//
//	data->conv_ctx = NULL;
//
//}
//*/
//
//
//// clean up the app data structure
//
//void clearAppData(AppData *data) {
//	/*
//	if (data->av_frame) av_free(data->av_frame);
//
//	if (data->gl_frame) av_free(data->gl_frame);
//
//	if (data->packet) av_free(data->packet);
//
//	if (data->codec_ctx) avcodec_close(data->codec_ctx);
//
//	if (data->fmt_ctx) avformat_free_context(data->fmt_ctx);
//	*/
//	glDeleteVertexArrays(1, &data->vao);
//
//	glDeleteBuffers(1, &data->vert_buf);
//
//	glDeleteBuffers(1, &data->elem_buf);
//
//	glDeleteTextures(1, &data->frame_tex);
//
////	initializeAppData(data);
//
//}
//
//void CutImage(int left_tran, int top_tran, int right_tran, int bottom_tran, Mat image, Mat& outimage)
//{
//
//	outimage = image(Rect(left_tran, top_tran, right_tran - left_tran, bottom_tran - top_tran));
//}
//
//// read a video frame
//
//bool readFrame(AppData *data,VideoCapture capture) {
//
//	Mat frame,smallframe;
//	capture >> frame;
//	curFrame++;
//	sprintf(imgPath,"./myImages/%d.jpg", curFrame);
//	imwrite(imgPath, frame);
//
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D,data->frame_tex);
//
//	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, data->frame_width,
//
//	data->frame_height, GL_BGR, GL_UNSIGNED_BYTE,
//
//	frame.data);
//
//
//	CutImage(0, 0, data->frame_width / 10.0, data->frame_height / 10, frame, smallframe);
//
//	//imwrite(imgPath, smallframe);
//
//	
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, data->small_tex);
//
//	
//
//
//	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, data->frame_width / 10.0,
//
//		data->frame_height / 10, GL_BGR, GL_UNSIGNED_BYTE,
//
//		smallframe.data);
//		
//	return true;
//
//}
//
//
//
//bool buildShader(std::string const &shader_source, GLuint &shader, GLenum type) {
//
//	int size = shader_source.length();
//
//
//
//	shader = glCreateShader(type);
//
//	char const *c_shader_source = shader_source.c_str();
//
//	glShaderSource(shader, 1, (GLchar const **)&c_shader_source, &size);
//
//	glCompileShader(shader);
//
//	GLint status;
//
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
//
//	if (status != GL_TRUE) {
//
//		std::cout << "failed to compile shader" << std::endl;
//
//		int length;
//
//		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
//
//		char *log = new char[length];
//
//		glGetShaderInfoLog(shader, length, &length, log);
//
//		std::cout << log << std::endl;
//
//		delete[] log;
//
//		return false;
//
//	}
//
//	return true;
//
//}
//
//
//
//// initialize shaders
//
//bool buildProgram(AppData *data) {
//
//	GLuint v_shader, f_shader;
//
//	if (!buildShader(vert_shader_source, v_shader, GL_VERTEX_SHADER)) {
//
//		std::cout << "failed to build vertex shader" << std::endl;
//
//		return false;
//
//	}
//
//
//
//	if (!buildShader(frag_shader_source, f_shader, GL_FRAGMENT_SHADER)) {
//
//		std::cout << "failed to build fragment shader" << std::endl;
//
//		return false;
//
//	}
//
//
//
//	data->program = glCreateProgram();
//
//	glAttachShader(data->program, v_shader);
//
//	glAttachShader(data->program, f_shader);
//
//	glLinkProgram(data->program);
//
//	GLint status;
//
//	glGetProgramiv(data->program, GL_LINK_STATUS, &status);
//
//	if (status != GL_TRUE) {
//
//		std::cout << "failed to link program" << std::endl;
//
//		int length;
//
//		glGetProgramiv(data->program, GL_INFO_LOG_LENGTH, &length);
//
//		char *log = new char[length];
//
//		glGetShaderInfoLog(data->program, length, &length, log);
//
//		std::cout << log << std::endl;
//
//		delete[] log;
//
//		return false;
//
//	}
//
//
//
//	data->uniforms[MVP_MATRIX] = glGetUniformLocation(data->program, "mvpMatrix");
//
//	data->uniforms[FRAME_TEX] = glGetUniformLocation(data->program, "frameTex");
//
//
//
//	data->attribs[VERTICES] = glGetAttribLocation(data->program, "vertex");
//
//	data->attribs[TEX_COORDS] = glGetAttribLocation(data->program, "texCoord0");
//
//
//
//	return true;
//
//}
//
//
//
//// draw frame in opengl context
//
//void drawFrame(AppData *data) {
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	//glUseProgram(data->program);
//
//	glActiveTexture(GL_TEXTURE0);
//
//	glBindTexture(GL_TEXTURE_2D, data->frame_tex);
//
//
//
//	glBindVertexArray(data->vao);
//
//	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
//
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//	glBindVertexArray(0);
//
////	glfwSwapBuffers(window);
//
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//
//
//
//static void error_callback(int error, const char* description)
//{
//	return;
//}
//
//void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
//{
//	cout << "im key envent" << endl;
//	if (action != GLFW_PRESS)
//	{
//		return;
//	}
//	switch (key)
//	{
//	case GLFW_KEY_ESCAPE:
//		glfwSetWindowShouldClose(window, GL_TRUE);
//		break;
//	default:
//		break;
//	}
//}
//
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//	if (action == GLFW_PRESS) switch (button)
//	{
//	case GLFW_MOUSE_BUTTON_LEFT:
//		strcpy(msg, "Mouse left button clicked");
//		break;
//	case GLFW_MOUSE_BUTTON_MIDDLE:
//		strcpy(msg, "Mouse middle button clicked!");
//		break;
//	case GLFW_MOUSE_BUTTON_RIGHT:
//		strcpy(msg, "Mouse right button clicked");
//		break;
//	default:
//		return;
//	}
//	return;
//}
//
//void cursor_position_callback(GLFWwindow* window, double x, double y)
//{
//	sprintf(msg, "Mouse position move to [%d:%d]", int(x), int(y));
//	xpos = float((x - width / 2) / width) * 2;
//	ypos = float(0 - (y - height / 2) / height) * 2;
//	return;
//
//}
//
//void scroll_callback(GLFWwindow* window, double x, double y)
//{
//	return;
//}
//
///**
//DWORD WINAPI DrawFrames(LPVOID lpParamter)
//{
//while (readFrame(&dataY)) {
//
////	running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
////glfwSetKeyCallback(window, key_callback);
//drawFrame(&dataY);
//
//}
//return 0;
//}
//
//*/
//
//void cube(int& shaderProgram, unsigned int& VAO, float* verticeys, int size)
//{
//
//	//！创建、编译我们的着色器程序
//	//顶点着色器
//	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource1, NULL);
//	glCompileShader(vertexShader);
//
//
//	//片元着色器
//	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource1, NULL);
//	glCompileShader(fragmentShader);
//
//	//链接着色器
//	shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	//别忘了释放着色器
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	unsigned int VBO;
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//
//	cout << sizeof(verticeys) << endl;
//
//	glBufferData(GL_ARRAY_BUFFER, size, verticeys, GL_STATIC_DRAW);
//
//
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//
//	glEnableVertexAttribArray(0);
//
//
//
//
//}
//
//
//void sanjiao(int& shaderProgram, unsigned int& VAO , float* verticeys ,int size)
//{
//	//！创建、编译我们的着色器程序
//	//顶点着色器
//	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource1, NULL);
//	glCompileShader(vertexShader);
//
//
//	//片元着色器
//	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource1, NULL);
//	glCompileShader(fragmentShader);
//
//	//链接着色器
//	shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	//别忘了释放着色器
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	unsigned int VBO;
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	
//
//	cout << sizeof(verticeys) << endl;
//
//	glBufferData(GL_ARRAY_BUFFER,size, verticeys, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//	glEnableVertexAttribArray(0);
//
//
//}
//
//
//int main(int argc, char *argv[]) {
//
//
//
//
//	AppData dataY;
//
//
//	// open video
//
//#ifdef LOCAL_VIDEO
//	//本地视频流
//	const char* filename = "./images/3.mp4";
//
//	VideoCapture capture(filename);
//
//
//#else
//	//摄像头视频流
//	VideoCapture capture(0);
//
//#endif
//	//打开文件视频流
//
//
//
//	/* #################################################以上全为处理视频流相关的操作     ##########################*/
//
//
//
//
//
//
//
//	// initialize glfw
//
//	if (!glfwInit()) {
//
//		std::cout << "glfw failed to init" << std::endl;
//
//		glfwTerminate();
//
//		clearAppData(&dataY);
//
//		return -1;
//
//	}
//
//	dataY.frame_height = (float)capture.get(CV_CAP_PROP_FRAME_HEIGHT);
//	dataY.frame_width = (float)capture.get(CV_CAP_PROP_FRAME_WIDTH);
//
//	// open a window
//
//	float aspect = (float)dataY.frame_width / (float)dataY.frame_height;
//
//
//	cout << "(float)data.codec_ctx->width" << (float)dataY.frame_width << endl;
//
//	cout << "(float)data.codec_ctx->height" << (float)dataY.frame_height << endl;
//
//
//
//	int adj_width = aspect * 500;
//
//	int adj_height = 500;
//
//
//	cout << "adj_width is " << adj_width << endl;
//
//	cout << "(float)data.codec_ctx->height" << (float)dataY.frame_height << endl;
//
//	/*
//	int adj_width = 600;
//
//	int adj_height = 800;
//	*/
//	glfwSetErrorCallback(error_callback);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	window = glfwCreateWindow(adj_width, adj_height, "LearnOpenGL", NULL, NULL);
//	if (window == NULL) {
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	//glfwSetKeyCallback(window, key_callback);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	/*glfwSetMouseButtonCallback(window, mouse_button_callback);
//	glfwSetCursorPosCallback(window, cursor_position_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	glfwGetFramebufferSize(window, &width, &height);*/
//	//framebuffer_size_callback(window, width, height);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//
//
//	// Ensure we can capture the escape key being pressed below
//	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
//	/*
//	// Hide the mouse and enable unlimited mouvement
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	*/
//	// Set the mouse at the center of the screen
//
//
//	/*
//
//	glfwPollEvents();
//	glfwSetCursorPos(window, adj_width / 2, adj_height / 2);
//
//	*/
//
//
//	/*
//	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
//
//	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
//
//	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	if (!glfwOpenWindow(adj_width, adj_height, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
//
//	std::cout << "failed to open window" << std::endl;
//
//	glfwTerminate();
//
//	clearAppData(&data);
//
//	return -1;
//
//	}
//
//	*/
//
//	// initialize opengl
//
//
//
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//
//	glEnable(GL_TEXTURE_2D);
//
//
//
//	// initialize shaders
//
//	if (!buildProgram(&dataY)) {
//
//		std::cout << "failed to initialize shaders" << std::endl;
//
//		glfwTerminate();
//
//		clearAppData(&dataY);
//
//		return -1;
//
//	}
//
//
//
//
//
//	// initialize renderable
//
//	glGenVertexArrays(1, &dataY.vao);
//
//	glBindVertexArray(dataY.vao);
//
//
//
//	glGenBuffers(1, &dataY.vert_buf);
//
//	glBindBuffer(GL_ARRAY_BUFFER, dataY.vert_buf);
//
//	/*
//	float quad[20] = {
//
//	-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
//
//	-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
//
//	1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
//
//	1.0f,  1.0f, 0.0f, 1.0f, 0.0f
//
//	};
//	*/
//
//
//	/*
//	放映一半的纹理
//	float quad[20] = {
//
//	-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
//
//	-1.0f, -1.0f, 0.0f, 0.0f, 0.5f,
//
//	1.0f, -1.0f, 0.0f, 0.5f, 0.5f,
//
//	1.0f,  1.0f, 0.0f, 0.5f, 0.0f
//
//	};
//	*/
//
//
//
//	/*
//	放映GL二维平面模型的一半空间
//
//	float quad[20] = {
//
//	-0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
//
//	-0.5f, -0.5f, 0.0f, 0.0f, 0.5f,
//
//	0.5f, -0.5f, 0.0f, 0.5f, 0.5f,
//
//	0.5f,  0.5f, 0.0f, 0.5f, 0.0f
//
//	};
//	*/
//
//
//
//	//放映Gl三维平面模型
//
//	float quad[] =
//	{
//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
//	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
//	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
//
//	};
//
//
//	//将视频投放到立方体的1个面上
//#ifdef VIDEO_ONE_FACE
//
//	float vertices[] = {
//		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
//		1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
//		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
//		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
//		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
//
//		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
//		1.0f, -1.0f, 1.0f,  0.0f, 0.0f,
//		1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
//		1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
//		-1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
//		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
//
//		-1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
//		-1.0f, 1.0f, -1.0f,  0.0f, 0.0f,
//		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
//		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
//		-1.0f, -1.0f, 1.0f,  0.0f, 0.0f,
//		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//
//		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//		1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
//		1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
//		1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
//		1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
//		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//
//		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
//		1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
//		1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
//		1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
//		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
//		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
//
//		-1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
//		1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
//		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//		-1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
//		-1.0f, 1.0f, -1.0f, 0.0f, 0.0f
//	};
//#else
//	//将视频投放到长方体的6个面上
//	float cuboid[] =
//	{
//		//后面
//		-1.0f, -0.5f, -0.5f, 0.44f, 0.56f,
//		1.0f, -0.5f, -0.5f, 0.89f, 0.56f,
//		1.0f, 0.5f, -0.5f, 0.89f, 0.0f,
//		1.0f,0.5f, -0.5f, 0.89f, 0.0f,
//		-1.0f, 0.5f, -0.5f, 0.44f, 0.0f,
//		-1.0f, -0.5f, -0.5f, 0.44f, 0.56f,
//
//
//		////前面
//		//-1.0f, -0.5f, 0.5f, 0.0f, 0.0f,
//		//1.0f, -0.5f, 0.5f, 1.0f, 0.0f,
//		//1.0f, 0.5f, 0.5f, 1.0f, 1.0f,
//		//1.0f, 0.5f, 0.5f, 1.0f, 1.0f,
//		//-1.0f, 0.5f, 0.5f, 0.0f, 1.0f,
//		//-1.0f, -0.5f, 0.5f, 0.0f, 0.0f,
//
//
//		//左侧面
//		-1.0f,0.5f, 0.5f, 0.0f, 0.56f,
//		-1.0f, 0.5f, -0.5f, 0.44f, 0.56f,
//		-1.0f, -0.5f, -0.5f, 0.44f, 1.0f,
//		-1.0f, -0.5f, -0.5f, 0.44f, 1.0f,
//		-1.0f, -0.5f, 0.5f, 0.0f, 1.0f,
//		-1.0f, 0.5f, 0.5f, 0.0f, 0.56f,
//
//		//右侧面
//
//
//
//		1.0f, 0.5f, 0.5f,1.0f, 1.0f,
//
//		1.0f, 0.5f, -0.5f, 1.0f, 0.56f,
//		1.0f, -0.5f, -0.5f, 0.89f, 0.56f,
//		1.0f, -0.5f, -0.5f,0.89f, 0.56f,
//		1.0f, -0.5f, 0.5f, 0.89f, 1.0f,
//		1.0f, 0.5f, 0.5f, 1.0f, 1.0f,
//
//		//底面
//		-1.0f, -0.5f, -0.5f, 0.44f, 0.56f,
//		1.0f, -0.5f, -0.5f,0.89f, 0.56f,
//		1.0f, -0.5f, 0.5f, 0.89f, 1.0f,
//		1.0f, -0.5f, 0.5f,  0.89f, 1.0f,
//		-1.0f, -0.5f, 0.5f, 0.44f, 1.0f,
//		-1.0f, -0.5f, -0.5f, 0.44f,0.56f
//	
//	};
//
//
//	//将视频投放到立方体的6个面上
//
//	float vertices[] = {
//
//		//后面
//		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
//		1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
//		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
//		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
//		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
//
//
//		//前面
//		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
//		1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
//		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//		-1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
//		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
//
//		//左侧面
//		-1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//		-1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
//		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
//		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
//		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
//		-1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//
//
//		//右侧面
//		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
//		1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
//
//		1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
//		1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
//		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
///*
//		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
//		1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
//		1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
//		1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
//		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
//		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
//
//		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
//		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f
//		*/
//	};
//
//	float cut_vertices[] = {
//
//		
//		//后面，完整的纹理
//
//		
//		-1.0f, -1.0f, -1.0f, 0.2f, 0.2f,
//		1.0f, -1.0f, -1.0f, 0.4f, 0.2f,
//		1.0f, 1.0f, -1.0f, 0.4f, 0.0f,
//		1.0f, 1.0f, -1.0f, 0.4f, 0.0f,
//		-1.0f, 1.0f, -1.0f, 0.2f,0.0f,
//		-1.0f, -1.0f, -1.0f, 0.2f, 0.2f,
//		/*
//		*/
//
//		/*
//		//前面
//		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
//		1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
//		1.0f, 1.0f, 1.0f, 1.0f, 0.5f,
//		1.0f, 1.0f, 1.0f, 1.0f,0.5f,
//		-1.0f, 1.0f, 1.0f, 0.0f, 0.5f,
//		-1.0f, -1.0f, 1.0f,0.0f, 0.0f,
//
//		*/
//		
//		//左侧面
//		-1.0f, 1.0f, 1.0f, 0.2f,0.0f,
//		-1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
//		-1.0f, -1.0f, -1.0f, 0.0f, 0.2f,
//		-1.0f, -1.0f, -1.0f,0.0f, 0.2f,
//		-1.0f, -1.0f, 1.0f, 0.2f, 0.2f,
//		-1.0f, 1.0f, 1.0f, 0.2f, 0.0f,
//		
//		
//
//		//右侧面
//		1.0f, 1.0f, 1.0f, 0.8f, 0.0f,
//		1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
//		1.0f, -1.0f, -1.0f, 1.0f, 0.2f,
//		1.0f, -1.0f, -1.0f, 1.0f, 0.2f,
//		1.0f, -1.0f, 1.0f, 0.8f, 0.2f,
//		1.0f, 1.0f, 1.0f, 0.8f, 0.0f,
//		
//		//底面
//		
//		-1.0f, -1.0f, -1.0f, 0.4f, 0.5f,
//		1.0f, -1.0f, -1.0f, 0.8f, 0.5f,
//		1.0f, -1.0f, 1.0f, 0.8f, 1.0f,
//		1.0f, -1.0f, 1.0f, 0.8f, 1.0f,
//		-1.0f, -1.0f, 1.0f, 0.5f, 1.0f,
//		-1.0f, -1.0f, -1.0f, 0.4f, 0.5f
//
//		/*
//		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
//		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
//		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f
//		*/
//	};
//
//#endif
//
//
//	//顶点和纹理以及法向量都是属性
//
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cuboid), cuboid, GL_STATIC_DRAW);
//
//
//
//
//	glVertexAttribPointer(dataY.attribs[VERTICES], 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
//
//		BUFFER_OFFSET(0));
//
//	glEnableVertexAttribArray(dataY.attribs[VERTICES]);
//
//
//
//
//	glVertexAttribPointer(dataY.attribs[TEX_COORDS], 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
//
//		BUFFER_OFFSET(12));
//
//	glEnableVertexAttribArray(dataY.attribs[TEX_COORDS]);
//
//
//
//
//	/*
//
//	glGenBuffers(1, &data.elem_buf);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.elem_buf);
//
//
//
//	unsigned char elem[6] = {
//
//	0, 1, 2,
//
//	0, 2, 3
//
//	};
//
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elem), elem, GL_STATIC_DRAW);
//
//	glBindVertexArray(0);
//
//	*/
//
//	//外面盒子的纹理
//	stbi_set_flip_vertically_on_load(true);
//
//	glActiveTexture(GL_TEXTURE0);
//
//	glGenTextures(1, &dataY.frame_tex);
//
//	glBindTexture(GL_TEXTURE_2D, dataY.frame_tex);
//
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dataY.frame_width, dataY.frame_height,
//
//		0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//
//	glUniform1i(dataY.uniforms[FRAME_TEX], 0);
//
//
//	//小立方体的纹理
//
////	unsigned int texture2;
//
//	stbi_set_flip_vertically_on_load(true);
//
//	glActiveTexture(GL_TEXTURE1);
//
//	glGenTextures(1, &dataY.small_tex);
//
//	glBindTexture(GL_TEXTURE_2D, dataY.small_tex);
//
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dataY.frame_width/10.0, dataY.frame_height/10.0,
//
//		0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//
//	glUniform1i(dataY.uniforms[FRAME_TEX], 0);
//
//	//小立方体的纹理
//
//
//
//
//
//
//
//	int shaderProgram;
//	unsigned int VAO;
//
//	sanjiao(shaderProgram, VAO ,verticeys,36);
//
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glUseProgram(shaderProgram);
//
//
//
//	int shaderProgram1;
//	unsigned int VAO1;
//
//	sanjiao(shaderProgram1, VAO1, verticeys2, 36);
//
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glUseProgram(shaderProgram1);
//
//	int shaderProgram2;
//	unsigned int VAO2;
//
//	cube(shaderProgram2, VAO2, InnerCube, 432);
//
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glUseProgram(shaderProgram2);
//
//	//深度测试
//	//glEnable(GL_DEPTH_TEST);
//
//	glUseProgram(dataY.program);
//
//
//	
//
//#ifdef NOTMVPSHADER
//
//
//	glm::mat4 view;
//	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
//
//	//	glUniformMatrix4fv(data.uniforms[MVP_MATRIX], 1, GL_FALSE, glm::value_ptr(mvp));
//
//	glUniformMatrix4fv(glGetUniformLocation(dataY.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
//
//
//
//	glm::mat4 projection;
//
//	projection = glm::perspective(glm::radians(45.0f), (float)dataY.frame_width / (float)dataY.frame_height, 0.1f, 100.0f);
//
//
//	glUniformMatrix4fv(glGetUniformLocation(dataY.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//
//
//	glm::mat4 model;
//	model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
//
//	glUniformMatrix4fv(glGetUniformLocation(dataY.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
//#else
//
//
//	glm::mat4 mvp = glm::ortho(-0.5f, 1.0f, -1.0f, 0.4f, -0.5f, 1.0f);
//
//
//
//
//	glUniformMatrix4fv(dataY.uniforms[MVP_MATRIX], 1, GL_FALSE, glm::value_ptr(mvp));
//
//#endif
//
//	
//
//	bool running = true;
//
//
//	//	HANDLE hThread = CreateThread(NULL, 0,DrawFrames, NULL, 0, NULL);
//
//	// run the application mainloop
//	
//	
//	/*
//	cout << "shaderProgram" << shaderProgram << endl;
//	cout << "VAO is" << VAO << endl;
//	*/
//	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//	
//	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
////	
//
//	/*
//	* 这里是一个习惯，上面的操作把属性都保存到了VAO中，这里只需要绑定就可以
//	* 如果要显示的东西不同，也只需要在这里绑定不同的东西就可以显示
//	*/
//	/*glBindVertexArray(VAO);
//	glDrawArrays(GL_TRIANGLES, 0, 3);
//	glfwSwapBuffers(window);
//*/
//	
//	
//
//
//	/*
//	glUseProgram(shaderProgram);
//	
//	*/
//	while (readFrame(&dataY,capture) && running) {
//
//
//		//glUseProgram(shaderProgram);
//		
//		//根据保存在
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		
//
//		glBindVertexArray(VAO1);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//
//
//		glBindVertexArray(VAO2);
//		glActiveTexture(GL_TEXTURE1);
//
//		glBindTexture(GL_TEXTURE_2D, dataY.small_tex);
//
//		
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//	//	cout <<" dataY.program 00000"<< dataY.program << endl;
//	//	cout << "dataY.VAO 00000" << dataY.vao << endl;
//		//	running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
//
//
//		glfwSwapBuffers(window);
//
//
//
//
//		drawFrame(&dataY);
//
//		
//
//		computeMatricesFromInputs(model);
//
//		model = getModelMatrix();
//		glUniformMatrix4fv(glGetUniformLocation(dataY.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
//		
//		/*
//		view = getViewMatrix();
//		glUniformMatrix4fv(glGetUniformLocation(dataY.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
//
//
//		projection = getProjectionMatrix();
//
//		glUniformMatrix4fv(glGetUniformLocation(dataY.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//		*/
//	//	glfwSwapBuffers(window);
//		glfwPollEvents();
//		//	glfwPollEvents();
//
//	}
//
//
//
//	// clean up
//
//	glfwTerminate();
//
//	clearAppData(&dataY);
//
//}
//
