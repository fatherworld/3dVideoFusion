//#include "videogl.h"
//
//// initialize the app data structure
///*
//void initializeAppData(AppData *data) {
//
//data->fmt_ctx = NULL;
//
//data->stream_idx = -1;
//
//data->video_stream = NULL;
//
//data->codec_ctx = NULL;
//
//data->decoder = NULL;
//
//data->av_frame = NULL;
//
//data->gl_frame = NULL;
//
//data->conv_ctx = NULL;
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
//	//	initializeAppData(data);
//
//}
//
//
//
//// read a video frame
//
//bool readFrame(AppData *data, VideoCapture capture) {
//
//	Mat frame;
//	capture >> frame;
//
//	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, data->frame_width,
//
//		data->frame_height, GL_BGR, GL_UNSIGNED_BYTE,
//
//		frame.data);
//
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
//	glBindTexture(GL_TEXTURE_2D, data->frame_tex);
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
//	glfwSwapBuffers(window);
//
//}
//
//
//
///*
//void framebuffer_size_callbackys(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//
//
//
//static void error_callbackys(int error, const char* description)
//{
//	return;
//}
//
//void key_callbackys(GLFWwindow * window, int key, int scancode, int action, int mods)
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
//void mouse_button_callbackys(GLFWwindow* window, int button, int action, int mods)
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
//void cursor_position_callbackys(GLFWwindow* window, double x, double y)
//{
//	sprintf(msg, "Mouse position move to [%d:%d]", int(x), int(y));
//	xpos = float((x - width / 2) / width) * 2;
//	ypos = float(0 - (y - height / 2) / height) * 2;
//	return;
//
//}
//
//void scroll_callbackys(GLFWwindow* window, double x, double y)
//{
//	return;
//}
//*/
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
//
//
////int main(int argc, char *argv[]) {
////
////
////
////
////	AppData dataY;
////
////
////	// open video
////
////#ifdef LOCAL_VIDEO
////	//本地视频流
////	const char* filename = "./images/1.mp4";
////
////	VideoCapture capture(filename);
////
////
////#else
////	//摄像头视频流
////	VideoCapture capture(0);
////
////#endif
////	//打开文件视频流
////
////
////
////	/* #################################################以上全为处理视频流相关的操作     ##########################*/
////
////
////
////
////
////
////
////	// initialize glfw
////
////	if (!glfwInit()) {
////
////		std::cout << "glfw failed to init" << std::endl;
////
////		glfwTerminate();
////
////		clearAppData(&dataY);
////
////		return -1;
////
////	}
////
////	dataY.frame_height = (float)capture.get(CV_CAP_PROP_FRAME_HEIGHT);
////	dataY.frame_width = (float)capture.get(CV_CAP_PROP_FRAME_WIDTH);
////
////	// open a window
////
////	float aspect = (float)dataY.frame_width / (float)dataY.frame_height;
////
////
////	cout << "(float)data.codec_ctx->width" << (float)dataY.frame_width << endl;
////
////	cout << "(float)data.codec_ctx->height" << (float)dataY.frame_height << endl;
////
////
////
////	int adj_width = aspect * 500;
////
////	int adj_height = 500;
////
////
////	cout << "adj_width is " << adj_width << endl;
////
////	cout << "(float)data.codec_ctx->height" << (float)dataY.frame_height << endl;
////
////	/*
////	int adj_width = 600;
////
////	int adj_height = 800;
////	*/
////	glfwSetErrorCallback(error_callback);
////	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
////	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
////	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
////
////	window = glfwCreateWindow(adj_width, adj_height, "LearnOpenGL", NULL, NULL);
////	if (window == NULL) {
////		std::cout << "Failed to create GLFW window" << std::endl;
////		glfwTerminate();
////		return -1;
////	}
////	glfwMakeContextCurrent(window);
////	//glfwSetKeyCallback(window, key_callback);
////	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
////	/*glfwSetMouseButtonCallback(window, mouse_button_callback);
////	glfwSetCursorPosCallback(window, cursor_position_callback);
////	glfwSetScrollCallback(window, scroll_callback);
////	glfwGetFramebufferSize(window, &width, &height);*/
////	//framebuffer_size_callback(window, width, height);
////
////	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
////		std::cout << "Failed to initialize GLAD" << std::endl;
////		return -1;
////	}
////
////
////
////	// Ensure we can capture the escape key being pressed below
////	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
////	/*
////	// Hide the mouse and enable unlimited mouvement
////	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
////	*/
////	// Set the mouse at the center of the screen
////
////
////	/*
////
////	glfwPollEvents();
////	glfwSetCursorPos(window, adj_width / 2, adj_height / 2);
////
////	*/
////
////
////	/*
////	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
////
////	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
////
////	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
////
////	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
////
////	if (!glfwOpenWindow(adj_width, adj_height, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
////
////	std::cout << "failed to open window" << std::endl;
////
////	glfwTerminate();
////
////	clearAppData(&data);
////
////	return -1;
////
////	}
////
////	*/
////
////	// initialize opengl
////
////
////
////	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
////
////	glEnable(GL_TEXTURE_2D);
////
////
////
////	// initialize shaders
////
////	if (!buildProgram(&dataY)) {
////
////		std::cout << "failed to initialize shaders" << std::endl;
////
////		glfwTerminate();
////
////		clearAppData(&dataY);
////
////		return -1;
////
////	}
////
////	glUseProgram(dataY.program);
////
////
////
////	// initialize renderable
////
////	glGenVertexArrays(1, &dataY.vao);
////
////	glBindVertexArray(dataY.vao);
////
////
////
////	glGenBuffers(1, &dataY.vert_buf);
////
////	glBindBuffer(GL_ARRAY_BUFFER, dataY.vert_buf);
////
////	/*
////	float quad[20] = {
////
////	-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
////
////	-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
////
////	1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
////
////	1.0f,  1.0f, 0.0f, 1.0f, 0.0f
////
////	};
////	*/
////
////
////	/*
////	放映一半的纹理
////	float quad[20] = {
////
////	-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
////
////	-1.0f, -1.0f, 0.0f, 0.0f, 0.5f,
////
////	1.0f, -1.0f, 0.0f, 0.5f, 0.5f,
////
////	1.0f,  1.0f, 0.0f, 0.5f, 0.0f
////
////	};
////	*/
////
////
////
////	/*
////	放映GL二维平面模型的一半空间
////
////	float quad[20] = {
////
////	-0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
////
////	-0.5f, -0.5f, 0.0f, 0.0f, 0.5f,
////
////	0.5f, -0.5f, 0.0f, 0.5f, 0.5f,
////
////	0.5f,  0.5f, 0.0f, 0.5f, 0.0f
////
////	};
////	*/
////
////
////	/*
////	放映Gl三维平面模型
////
////	float quad[180] =
////	{
////	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
////	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
////	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
////	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
////	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
////	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
////	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
////	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
////	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
////	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
////	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
////	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
////	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
////	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
////	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
////	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
////	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
////	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
////	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
////	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
////	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
////	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
////	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
////	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
////	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
////	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
////	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
////	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
////	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
////	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
////	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
////	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
////	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
////	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
////	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
////	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
////
////	};
////	*/
////
////	//将视频投放到立方体的1个面上
////#ifdef VIDEO_ONE_FACE
////
////	float vertices[] = {
////		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
////		1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
////		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
////		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
////		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
////		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
////
////		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
////		1.0f, -1.0f, 1.0f,  0.0f, 0.0f,
////		1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
////		1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
////		-1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
////		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
////
////		-1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
////		-1.0f, 1.0f, -1.0f,  0.0f, 0.0f,
////		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
////		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
////		-1.0f, -1.0f, 1.0f,  0.0f, 0.0f,
////		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
////
////		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
////		1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
////		1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
////		1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
////		1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
////		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
////
////		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
////		1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
////		1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
////		1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
////		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
////		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
////
////		-1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
////		1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
////		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
////		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
////		-1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
////		-1.0f, 1.0f, -1.0f, 0.0f, 0.0f
////	};
////#else
////
////	//将视频投放到立方体的6个面上
////
////	float vertices[] = {
////		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
////		1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
////		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
////		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
////		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
////		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
////
////		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
////		1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
////		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
////		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
////		-1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
////		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
////
////		-1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
////		-1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
////		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
////		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
////		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
////		-1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
////
////		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
////		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
////		1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
////		1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
////		1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
////		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
////
////		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
////		1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
////		1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
////		1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
////		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
////		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,
////
////		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
////		1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
////		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
////		1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
////		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
////		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f
////	};
////
////
////
////#endif
////
////
////
////	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
////
////
////
////
////	glVertexAttribPointer(dataY.attribs[VERTICES], 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
////
////		BUFFER_OFFSET(0));
////
////	glEnableVertexAttribArray(dataY.attribs[VERTICES]);
////
////
////
////
////	glVertexAttribPointer(dataY.attribs[TEX_COORDS], 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
////
////		BUFFER_OFFSET(12));
////
////	glEnableVertexAttribArray(dataY.attribs[TEX_COORDS]);
////
////	/*
////
////	glGenBuffers(1, &data.elem_buf);
////
////	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.elem_buf);
////
////
////
////	unsigned char elem[6] = {
////
////	0, 1, 2,
////
////	0, 2, 3
////
////	};
////
////	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elem), elem, GL_STATIC_DRAW);
////
////	glBindVertexArray(0);
////
////	*/
////
////	stbi_set_flip_vertically_on_load(true);
////
////	glActiveTexture(GL_TEXTURE0);
////
////	glGenTextures(1, &dataY.frame_tex);
////
////	glBindTexture(GL_TEXTURE_2D, dataY.frame_tex);
////
////	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
////
////	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
////
////	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
////
////	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////
////	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////
////	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dataY.frame_width, dataY.frame_height,
////
////		0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
////
////	glUniform1i(dataY.uniforms[FRAME_TEX], 0);
////
////
////	//深度测试
////	//glEnable(GL_DEPTH_TEST);
////
////
////#ifdef NOTMVPSHADER
////
////
////	glm::mat4 view;
////	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
////
////	//	glUniformMatrix4fv(data.uniforms[MVP_MATRIX], 1, GL_FALSE, glm::value_ptr(mvp));
////
////	glUniformMatrix4fv(glGetUniformLocation(dataY.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
////
////
////
////	glm::mat4 projection;
////
////	projection = glm::perspective(glm::radians(45.0f), (float)dataY.frame_width / (float)dataY.frame_height, 0.1f, 100.0f);
////
////
////	glUniformMatrix4fv(glGetUniformLocation(dataY.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
////
////
////	glm::mat4 model;
////	model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
////
////	glUniformMatrix4fv(glGetUniformLocation(dataY.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
////#else
////
////
////	glm::mat4 mvp = glm::ortho(-0.5f, 1.0f, -1.0f, 0.4f, -0.5f, 1.0f);
////
////
////
////
////	glUniformMatrix4fv(dataY.uniforms[MVP_MATRIX], 1, GL_FALSE, glm::value_ptr(mvp));
////
////#endif
////
////
////	bool running = true;
////
////
////	//	HANDLE hThread = CreateThread(NULL, 0,DrawFrames, NULL, 0, NULL);
////
////	// run the application mainloop
////
////
////
////
////
////	while (readFrame(&dataY, capture) && running) {
////
////
////
////
////		//	running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
////		drawFrame(&dataY);
////
////		computeMatricesFromInputs(model);
////
////		model = getModelMatrix();
////		glUniformMatrix4fv(glGetUniformLocation(dataY.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
////		/*
////		view = getViewMatrix();
////		glUniformMatrix4fv(glGetUniformLocation(dataY.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
////
////
////		projection = getProjectionMatrix();
////
////		glUniformMatrix4fv(glGetUniformLocation(dataY.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
////		*/
////		glfwPollEvents();
////		//	glfwPollEvents();
////
////	}
////
////
////
////	// clean up
////
////	glfwTerminate();
////
////	clearAppData(&dataY);
////
////}
////
////
////
////
////
/////*
////void main()
////
////{
////
//////VideoCapture capture(0);
////
////VideoCapture capture(0);
////
////Mat frame;
////
////
////
////while (capture.isOpened())
////
////{
////
////capture >> frame;
////
////// capture.read(fram); //另一种获取帧的方式
////
////imshow("video", frame);
////
////
////
////if (waitKey(20) == 27)  //资料说明，在显示图像的时候，每秒显示27、28帧的时候，我们看到的视频是流畅的
////
////{
////
////break;
////
////}
////
////}
////
////waitKey(0);
////
////}
