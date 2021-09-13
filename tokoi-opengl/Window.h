/**
 * @file Window.h
 * @brief 
 * @author kitayama
 * @date 2021/09/13
 */
#ifndef SIN5DDD_OPENGL_STUDY_WINDOW_H
#define SIN5DDD_OPENGL_STUDY_WINDOW_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
	GLFWwindow* const window;
	GLfloat aspect;
	GLfloat size[2];
	GLfloat scale;
	GLfloat location[2];

	int keyStatus;

public:
	Window(int width = 640, int height = 480, const char* title = "Hello!")
			: window(glfwCreateWindow(width, height, title, nullptr, nullptr)),
			  scale(100.0f),
			  location{0.0f, 0.0f},
			  keyStatus(GLFW_RELEASE) {
		if(window == nullptr) {
			std::cerr << "Couldn't create GLFW window." << std::endl;
			exit(1);
		}

		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		if(glewInit() != GLEW_OK) {
			std::cerr << "Couldn't initialize GLEW." << std::endl;
			exit(1);
		}

		// using vsync
		glfwSwapInterval(1);

		// setting callback functions
		glfwSetWindowSizeCallback(window, resize);
		glfwSetScrollCallback(window, wheel);
		glfwSetKeyCallback(window, keyboard);

		// コールバック関数用
		// スタティックメソッドから参照できるように、このインスタンスのポインタを登録する
		glfwSetWindowUserPointer(window, this);

		resize(window, width, height);
	}

	static void resize(GLFWwindow* const window, int width, int height) {
		int fbWidth, fbHeight;
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
		glViewport(0, 0, fbWidth, fbHeight);

		auto* const instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));
		if(instance != nullptr) {
			instance->size[0] = static_cast<GLfloat>(width);
			instance->size[1] = static_cast<GLfloat>(height);
		}
	}

	static void wheel(GLFWwindow* const window, double x, double y) {
		auto* const instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));
		if(instance != nullptr) {
			instance->scale += static_cast<GLfloat>(y * 10);
		}
	}

	static void keyboard(GLFWwindow* const window, int key, int scancode, int action, int mods) {
		auto* const instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));
		if(instance != nullptr) {
			instance->keyStatus = action;
		}
	}

	GLfloat getAspect() const { return aspect; }

	const GLfloat* getSize() const { return size; }

	GLfloat getScale() const { return scale; }

	const GLfloat* getLocation() const { return location; }

	virtual ~Window() {
		glfwDestroyWindow(window);
	}

	/// 実質的なGLFWメインループ
	/// \return
	explicit operator bool() {
		if(keyStatus == GLFW_RELEASE) {
			glfwWaitEvents();
		} else {
			glfwPollEvents();
		}

		// key state
		if(glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_RELEASE) {
			location[0] -= 2.0f / size[0];
		}
		if(glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_RELEASE) {
			location[0] += 2.0f / size[0];
		}
		if(glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_RELEASE) {
			location[1] -= 2.0f / size[1];
		}
		if(glfwGetKey(window, GLFW_KEY_UP) != GLFW_RELEASE) {
			location[1] += 2.0f / size[1];
		}

		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE) {
			// getting mouse pos
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			location[0] = static_cast<GLfloat>(x) * 2.0f / size[0] - 1.0f;
			location[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / size[1];
		}

		return !glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE);
	}

	void swapBuffers() const {
		glfwSwapBuffers(window);
	}
};


#endif //SIN5DDD_OPENGL_STUDY_WINDOW_H
