//#pragma once
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
//#include "stb_image.h"
//static HANDLE g_Mutex;
//
//using namespace std;
//using namespace cv;
//#define STB_IMAGE_IMPLEMENTATION
//
//
////#define VIDEO_ONE_FACE YS
//#define NOTMVPSHADER Y
//#define LOCAL_VIDEO YS
//extern GLFWwindow* window;
//
///*
//ffmpeg部分
//extern "C"
//{
//#include "libswscale/swscale.h"
////编码
//#include "libavcodec/avcodec.h"
////封装格式处理
//#include "libavformat/avformat.h"
////像素处理
//#include "libswscale/swscale.h"
//};
//*/
//
//#pragma warning(disable:4996)
//
//
//
//static char msg[128] = { 0 };
////GLFWwindow* window = NULL;
//static GLint width, height;
//static GLfloat ratioY;
//static GLfloat xpos, ypos;
//static GLfloat fScale = 1.0f;
//static GLfloat rquad = 0.0f;
////AppData dataY;
//
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
//	/*
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
//} AppData;
//
//void clearAppData(AppData *data);
//
//
//bool readFrame(AppData *data, VideoCapture capture);
//
//bool buildShader(std::string const &shader_source, GLuint &shader, GLenum type);
//
//bool buildProgram(AppData *data);
//
//void drawFrame(AppData *data);
//
//
//
///*
//void framebuffer_size_callbackys(GLFWwindow* window, int width, int height);
//
//void key_callbackys(GLFWwindow * window, int key, int scancode, int action, int mods);
//
//void mouse_button_callbackys(GLFWwindow* window, int button, int action, int mods);
//
//void cursor_position_callbackys(GLFWwindow* window, double x, double y);
//
//void scroll_callbackys(GLFWwindow* window, double x, double y);
//*/