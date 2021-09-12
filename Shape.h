//
// Created by kitayama on 2021/09/12.
//

#ifndef OPENGL_STUDY_SHAPE_H
#define OPENGL_STUDY_SHAPE_H

#include <memory>
#include "Object.h"

class Shape {
	std::shared_ptr<const Object> object;
protected:
	const GLsizei vertex_count;
public:
	Shape(GLint size, GLsizei vertex_count, const Object::Vertex* vertex)
			: object(new Object(size, vertex_count, vertex)),
			  vertex_count(vertex_count) { }

	void draw() const {
		object->bind();
		execute();
	}

	virtual void execute() const{
		glDrawArrays(GL_LINE_LOOP, 0, vertex_count);
	}
};

#endif //OPENGL_STUDY_SHAPE_H
