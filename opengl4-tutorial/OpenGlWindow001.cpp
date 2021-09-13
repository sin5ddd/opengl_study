/**
 * @file OpenGlWindow001.cpp
 * @brief 
 * @author kitayama
 * @date 2021/09/13
 */
#include "OpenGlWindow001.h"

void OpenGLWindow001::initializeScene() {
	glClearColor(0, 0.5f, 1.0f, 1.0f);
}

void OpenGLWindow001::renderScene() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLWindow001::updateScene() {
	if(keyPressedOnce(GLFW_KEY_ESCAPE)){
		closeWindow();
	}
}
