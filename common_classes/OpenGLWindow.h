/**
 * @file OpenGlWindow.h
 * @brief 
 * @author kitayama
 * @date 2021/09/13
 */
#ifndef SIN5DDD_OPENGL_STUDY_OPENGLWINDOW_H
#define SIN5DDD_OPENGL_STUDY_OPENGLWINDOW_H

#include <string>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class OpenGLWindow {
public:
	OpenGLWindow();

	bool createOpenGLWindow(const std::string& windowTitle, int majorVersion, int minorVersion, bool showFullscreen);

	[[nodiscard]] GLFWwindow* getWindow() const;

	void runApp();

	virtual void initializeScene() { }

	virtual void renderScene() { }

	virtual void updateScene() { }

	virtual void releaseScene() { }

	bool keyPressed(int keycode) const;

	bool keyPressedOnce(int keycode);

	void closeWindow(bool hasErrorOccurred = false);

	bool hasErrorOccurred() const;

	glm::mat4 getProjectionMatrix() const;

	glm::mat4 getOrthoProjectionMatrix() const;

	float sof(float value) const;

	double sof(double value) const;

	double getTimeDelta() const;

	int getFPS() const;

	void setVerticalSynchronization(bool enable);

	int getScreenWidth() const;

	int getScreenHeight() const;

	glm::ivec2 getOpenGLCursorPosition() const;

	static OpenGLWindow* getDefaultWindow();

protected:
	virtual void onWindowSizeChanged(int width, int height) { }

	virtual void onMouseButtonPressed(int button, int action) { }

	virtual void onMouseWheelScroll(double scrollOffsetX, double scrollOffsetY) { }

private:
	GLFWwindow* _window = nullptr;
	bool _keyWasPressed[512];
	bool _hasErrorOccurred = false;

	glm::mat4 _projectionMatrix;
	glm::mat4 _orthoMatrix;

	void recalculateProjectionMatrix();

	double _lastFrameTime = 0.0;
	double _lastFrameTimeFPS = 0.0;
	double _timeDelta = 0.0;
	int _FPS = 0;
	int _nextFPS = 0;
	bool _isVSyncEnabled = false;

	bool _hasMouseBeenScrolled = false;
	double _scrollOffsetX = 0.0;
	double _scrollOffsetY = 0.0;

	int screenWidth_{0};
	int screenHeight_{0};


	void updateDeltaTimeAndFPS();

	void onWindowSizeChangedInternal(int width, int height);

	static void onWindowSizeChangedStatic(GLFWwindow* window, int width, int height);

	static void onMouseButtonPressedStatic(GLFWwindow* window, int button, int action, int mods);

	static void onMouseWheelScrollStatic(GLFWwindow* window, double scrollOffsetX, double scrollOffsetY);

	static std::map<GLFWwindow*, OpenGLWindow*> _windows;
};


#endif //SIN5DDD_OPENGL_STUDY_OPENGLWINDOW_H
