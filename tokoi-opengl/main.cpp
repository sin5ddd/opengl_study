#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Matrix.h"
#include "Shape.h"

GLboolean printShaderInfoLog(GLuint shader, const char* str) {
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) { std::cerr << "Compile Error in" << str << std::endl; }

	GLsizei buf_size;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &buf_size);
	if(buf_size > 1) {
		std::vector<GLchar> info_log(buf_size);
		GLsizei length;
		glGetShaderInfoLog(shader, buf_size, &length, &info_log[0]);
		std::cerr << &info_log[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}

GLboolean printProgramInfoLog(GLuint program) {
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if(status == GL_FALSE) { std::cerr << "Link Error." << std::endl; }
	GLsizei buff_size;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &buff_size);

	if(buff_size > 1) {
		std::vector<GLchar> info_log(buff_size);
		GLsizei length;
		glGetProgramInfoLog(program, buff_size, &length, &info_log[0]);
		std::cerr << &info_log[0] << std::endl;
	}
	return static_cast<GLboolean>(status);
}

GLuint createProgram(const char* vsrc, const char* fsrc) {
	const GLuint program(glCreateProgram());
	if(vsrc != nullptr) {
		const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
		glShaderSource(vobj, 1, &vsrc, nullptr);
		glCompileShader(vobj);

		if(printShaderInfoLog(vobj, "vertex shader")) {
			glAttachShader(program, vobj);
		}
		glDeleteShader(vobj);
	}

	if(fsrc != nullptr) {
		const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
		glShaderSource(fobj, 1, &fsrc, nullptr);
		glCompileShader(fobj);

		if(printShaderInfoLog(fobj, "fragment shader")) {
			glAttachShader(program, fobj);
		}
		glDeleteShader(fobj);
	}

	glBindAttribLocation(program, 0, "position");
	glBindFragDataLocation(program, 0, "fragment");
	glLinkProgram(program);
	if(printProgramInfoLog(program)) {
		return program;
	} else {
		glDeleteProgram(program);
		return 0;
	}
}

bool readShaderSource(const char* name, std::vector<GLchar>& buffer) {
	if(name == nullptr) { return false; }
	std::ifstream file(name, std::ios::binary);
	if(file.fail()) {
		std::cerr << "Error: Couldn't open shader source file: " << name << std::endl;
		return false;
	}

	file.seekg(0L, std::ios::end);
	GLsizei length = static_cast<GLsizei>(file.tellg());

	buffer.resize(length + 1); // resize memory to fit file length
	file.seekg(0L, std::ios::beg); // start reading
	file.read(buffer.data(), length);
	buffer[length] = '\0';

	if(file.fail()) { // couldn't read
		std::cerr << "Error: Could not read shader source file: " << name << std::endl;
		file.close();
		return false;
	}

	file.close();
	return true;
}

GLuint loadProgram(const char* vert, const char* frag) {
	std::vector<GLchar> v_src;
	const bool v_stat(readShaderSource(vert, v_src));
	std::vector<GLchar> f_src;
	const bool f_stat(readShaderSource(frag, f_src));
	return v_stat && f_stat ? createProgram(v_src.data(), f_src.data()) : 0;
}


constexpr Object::Vertex rectangleVertex[] = {
		{-0.5f, -0.5f},
		{0.5f,  -0.5f},
		{0.5f,  0.5f},
		{-0.5f, 0.5f}
};

int main() {
	if(glfwInit() == GL_FALSE) {
		std::cerr << "Couldn't Initialize GLFW." << std::endl;
		return 1;
	}

	atexit(glfwTerminate);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window window;

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	auto program(loadProgram("resources/point.vert", "resources/point.frag"));

	const auto modelViewLoc(glGetUniformLocation(program, "modelView"));
	const auto projectionLoc(glGetUniformLocation(program, "projection"));

	std::unique_ptr<const Shape> shape(new Shape(2, 4, rectangleVertex));

	while (window) {
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);

		// OrthoProjectionMatrixを求める
		const GLfloat* const size(window.getSize());
		const GLfloat scale(window.getScale() * 2.0f);
		const GLfloat w(size[0] / scale), h(size[1] / scale);
		const Matrix projection(Matrix::orthogonal(-w, w, -w, h, 1.0f, 10.0f));

		// ModelProjectionMatrixを求める
		const GLfloat* const location(window.getLocation());
		const Matrix model(Matrix::translate(location[0], location[1], 0.0f));

//		const Matrix scaling(Matrix::scale(scale / size[0], scale / size[1], 1.0f));

		// 平行移動
//		const GLfloat* const position(window.getLocation());
//		const Matrix translation(Matrix::translate(position[0], position[1], 0.0f));

		// 変換行列
//		const Matrix model(translation * scaling);
//		const Matrix view(Matrix::lookAt(0.0f, 0.0f, 0.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f));
		const Matrix view(Matrix::lookAt(3.0f, 4.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
		const Matrix modelView(view * model);

		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data());
		glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, modelView.data());



		// draw
		shape->draw();

		window.swapBuffers();
	}
}
