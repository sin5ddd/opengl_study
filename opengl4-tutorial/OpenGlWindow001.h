/**
 * @file OpenGlWindow001.h
 * @brief 
 * @author kitayama
 * @date 2021/09/13
 */
#ifndef SIN5DDD_OPENGL_STUDY_OPENGLWINDOW001_H
#define SIN5DDD_OPENGL_STUDY_OPENGLWINDOW001_H

#include "../common_classes/OpenGLWindow.h"

class OpenGLWindow001 : public OpenGLWindow {
public:
	void initializeScene() override;

	void renderScene() override;

	void updateScene() override;
};


#endif //SIN5DDD_OPENGL_STUDY_OPENGLWINDOW001_H
