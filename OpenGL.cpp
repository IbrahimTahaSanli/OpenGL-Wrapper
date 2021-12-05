#ifndef __OPENGLH__
#define __OPENGLH__
#include "OpenGL.hpp"
#endif

GL::OpenGL::OpenGL(Window::Window* window) {


	GLuint PixelFormat;
	this->pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		window->Bits,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	if (!(PixelFormat = ChoosePixelFormat(window->hDeviceContext, &pfd))) {
		this->DeleteContext();
		MessageBox(0, L"Couldnt Choose Pixel Format", L"Errorü", MB_OK | MB_ICONEXCLAMATION);
		goto end;
	}

	if (!SetPixelFormat(window->hDeviceContext, PixelFormat, &pfd)) {
		this->DeleteContext();
		MessageBox(0, L"Couldnt Set Pixel Format", L"Errorü", MB_OK | MB_ICONEXCLAMATION);
		goto end;
	}

	if (!(window->hRenderingContext = wglCreateContext(window->hDeviceContext))) {
		this->DeleteContext();
		MessageBox(0, L"Couldnt Create OpenGL Context", L"Errorü", MB_OK | MB_ICONEXCLAMATION);
		goto end;
	}

	if (!wglMakeCurrent(window->hDeviceContext, window->hRenderingContext)) {
		this->DeleteContext();
		MessageBox(0, L"Couldnt Set Context", L"Errorü", MB_OK | MB_ICONEXCLAMATION);
		goto end;
	}

	if (InitOpenGL() == GL::GL_FALSE) {
		this->DeleteContext();
		MessageBox(0, L"Couldnt Initialize GLEW", L"Errorü", MB_OK | MB_ICONEXCLAMATION);
		goto end;
	}

	//GL::glShadeModel(GL_SMOOTH);

	GL::glClearColor(0.f, 0.f, 0.4f, 1.f);

	//	GL::glClearDepth(1.f);
	//	glEnable(GL_DEPTH_TEST);
	//	glDepthFunc(GL_LEQUAL);

	this->ContextWindow = window;
end:
	;
}

void GL::OpenGL::DeleteContext() {
	if (this->ContextWindow->hRenderingContext) {
		if (!wglMakeCurrent(0, 0))
			MessageBox(0, L"Couldnt Set Null Current Wgl Context", L"Errorü", MB_OK | MB_ICONEXCLAMATION);
		if (!wglDeleteContext(this->ContextWindow->hRenderingContext))
			MessageBox(0, L"Couldnt Delete OpenGL COntext", L"Errorü", MB_OK | MB_ICONEXCLAMATION);

		this->ContextWindow->hRenderingContext = 0;
	}
}

void GL::OpenGL::ResizeViewport(unsigned int Width, unsigned int Height) {
	glViewport(0, 0, Width, Height == 0 ? 1 : Height);
}


int GL::OpenGL::InitOpenGL() {
	mod = LoadLibrary(L"opengl32.dll");

	//I should use wglGetProcAddress
	GL::glBindBuffer = (_glBindBuffer*)GetProcAddress(mod, "glBindBuffer");
	GL::glBindVertexArray = (_glBindVertexArray*)GetProcAddress(mod, "glBindVertexArray");
	GL::glBufferData = (_glBufferData*)GetProcAddress(mod, "glBufferData");
	GL::glClear = (_glClear*)GetProcAddress(mod, "glClear");
	GL::glDeleteBuffers = (_glDeleteBuffers*)GetProcAddress(mod, "glDeleteBuffers");
	GL::glDeleteVertexArrays = (_glDeleteVertexArrays*)GetProcAddress(mod, "glDeleteVertexArrays");
	GL::glDrawArrays = (_glDrawArrays*)GetProcAddress(mod, "glDrawArrays");
	GL::glEnableVertexAttribArray = (_glEnableVertexAttribArray*)GetProcAddress(mod, "glEnableVertexAttribArray");
	GL::glGenBuffers = (_glGenBuffers*)GetProcAddress(mod, "glGenBuffers");
	GL::glGenVertexArrays = (_glGenVertexArrays*)GetProcAddress(mod, "glGenVertexArrays");
	GL::glGenBuffers = (_glGenBuffers*)GetProcAddress(mod, "glGenBuffers");
	GL::glGetUniformLocation = (_glGetUniformLocation*)GetProcAddress(mod, "glGetUniformLocation");
	GL::glUniformMatrix4fv = (_glUniformMatrix4fv*)GetProcAddress(mod, "glUniformMatrix4fv");
	GL::glUseProgram = (_glUseProgram*)GetProcAddress(mod, "glUseProgram");
	GL::glVertexAttribPointer = (_glVertexAttribPointer*)GetProcAddress(mod, "glVertexAttribPointer");
	GL::glClearColor = (_glClearColor*)GetProcAddress(mod, "glClearColor");
	GL::glDepthFunc = (_glDepthFunc*)GetProcAddress(mod, "glDepthFunc");
	GL::glEnable = (_glEnable*)GetProcAddress(mod, "glEnable");
	GL::glViewport = (_glViewport*)GetProcAddress(mod, "glViewport");
	GL::glAttachShader = (_glAttachShader*)GetProcAddress(mod, "glAttachShader");
	GL::glCompileShader = (_glCompileShader*)GetProcAddress(mod, "glCompileShader");
	GL::glCreateProgram = (_glCreateProgram*)GetProcAddress(mod, "glCreateProgram");
	GL::glCreateShader = (_glCreateShader*)GetProcAddress(mod, "glCreateShader");
	GL::glDeleteShader = (_glDeleteShader*)GetProcAddress(mod, "glDeleteShader");
	GL::glDetachShader = (_glDetachShader*)GetProcAddress(mod, "glDetachShader");
	GL::glGetProgramInfoLog = (_glGetProgramInfoLog*)GetProcAddress(mod, "glGetProgramInfoLog");
	GL::glGetProgramiv = (_glGetProgramiv*)GetProcAddress(mod, "glGetProgramiv");
	GL::glGetShaderInfoLog = (_glGetShaderInfoLog*)GetProcAddress(mod, "glGetShaderInfoLog");
	GL::glGetShaderiv = (_glGetShaderiv*)GetProcAddress(mod, "glGetShaderiv");
	GL::glLinkProgram = (_glLinkProgram*)GetProcAddress(mod, "glLinkProgram");
	GL::glShaderSource = (_glShaderSource*)GetProcAddress(mod, "glShaderSource");


	return GL::GL_TRUE;

}