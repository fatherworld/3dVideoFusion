#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>	//要用到OpenGL的函数就要包含这个头文件

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader {
public:
	//程序ID
	unsigned int ID;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//使用着色器
	void use();
	//设置uniform变量
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, float value[]) const;
};

#endif