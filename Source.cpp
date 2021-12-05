#pragma once
#include "OpenGL.cpp"
#include "Window.hpp"


int main() {
	Window::Window rootWindow(L"WrappeerTestClass", L"Title", 1024, 768, 16, 0);
	/*
	GL::OpenGL openGL(&rootWindow);

	GL::GLuint vertexarray;
	GL::glGenVertexArrays(1, &vertexarray);
	GL::glBindVertexArray(vertexarray);

	static const GL::GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
	};

	// This will identify our vertex buffer
	GL::GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	GL::glGenBuffers(1, &vertexbuffer);

#define GL_ARRAY_BUFFER 34962
#define GL_STATIC_DRAW 35044 
#define GL_FLOAT 5126
#define GL_TRIANGLES 4
	// The following commands will talk about our 'vertexbuffer' buffer
	GL::glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	GL::glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GL::glEnableVertexAttribArray(0);
	GL::glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	GL::glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL::GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangle !
	GL::glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	*/

	while (rootWindow.PoolMessages()) {
		
		if (!rootWindow.ShouldQUit)
			break;
	}
	rootWindow.DestroyThisWindow();

	return 0;
}