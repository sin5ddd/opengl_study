//
// Created by kitayama on 2021/09/12.
//

#ifndef OPENGL_STUDY_OBJECT_H
#define OPENGL_STUDY_OBJECT_H

#include <GL/glew.h>

class Object {
	GLuint vao;
	GLuint vbo;

public:
	struct Vertex {
			GLfloat position[2];
	};

	Object(GLint size, GLsizei vertex_count, const Vertex* vertex) {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertex, GL_STATIC_DRAW);

		// make vbo to link "in" variable, enabled get from shaders
		glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	}

	virtual ~Object(){
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	void bind() const{
		glBindVertexArray(vao);
	}

private:
	// singleton
	Object(const Object &o);
	Object &operator=(const Object &o);
};

#endif //OPENGL_STUDY_OBJECT_H
