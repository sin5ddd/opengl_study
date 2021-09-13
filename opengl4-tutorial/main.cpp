//
// Created by kitayama on 2021/09/13.
//

#include <iostream>
#include "OpenGlWindow001.h"

int main() {
	const std::string& title = "creating gl4 window";
	int majorVersion = 4;
	int minorVersion = 4;

	char answer;
	std::cout << "Would you like to run in fullscreen mode? (y/n): ";
	std::cin >> answer;
	bool showFullscreen = std::tolower(answer) == 'y';

	OpenGLWindow001 w;
	if(!w.createOpenGLWindow(title, majorVersion, minorVersion,showFullscreen)){
		printf("Failed to create window with OpenGL context %d.%d!\n", majorVersion, minorVersion);
		return 1;
	}

	w.runApp();
	return 0;

}