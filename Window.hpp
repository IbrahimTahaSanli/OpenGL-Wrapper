#ifndef __WINDOWH__
#define __WINDOWH__


#pragma once
#include <Windows.h>

namespace Window {

	//typedef void (OpenGL::*ResizeFunc)( unsigned int Width, unsigned int Height);

	class Window {
		//ResizeFunc* _resizeFunc;
	public:


		HGLRC			hRenderingContext;
		HDC				hDeviceContext;
		HWND			hWindowHand;
		HINSTANCE		hInstance;

		LPCWSTR			ClassName;

		int				keys[256];
		int				WindowActive;
		int				FullScreen;
		int				ShouldQUit = 0;
		unsigned int	ResX, ResY;
		unsigned char	Bits;

		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

		Window(LPCWSTR ClassName, LPCWSTR Title, unsigned int Width, unsigned int Height, char Bits, int Fullscreen);

		int		PoolMessages();
		//void	FixedResizeFunction(unsigned int Width, unsigned int Height);
		void	DestroyThisWindow();
	};


}

#endif