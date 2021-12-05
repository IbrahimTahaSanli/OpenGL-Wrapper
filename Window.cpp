#include "Window.hpp"


Window::Window::Window(LPCWSTR ClassName = L"Class", LPCWSTR Title = L"Title", unsigned int Width = 720, unsigned int Height = 640, char Bits = 16, int Fullscreen = 0) {
	DWORD dwExtendedStyle;
	DWORD dwStyle;


	this->hInstance = GetModuleHandle(NULL);

	WNDCLASS WindowClass;
	WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WindowClass.lpfnWndProc = WndProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = this->hInstance;
	WindowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	WindowClass.hCursor = LoadCursorW(NULL, IDC_ARROW);
	WindowClass.hbrBackground = 0;
	WindowClass.lpszMenuName = 0;
	WindowClass.lpszClassName = ClassName;

	if (!RegisterClass(&WindowClass)) {
		MessageBox(NULL, L"Couldn't Register Class", L"Errorü", MB_OK | MB_ICONWARNING);
		goto end;
	}

	if (FullScreen) {
		DEVMODE DeviceModeScreenSettings;
		memset(&DeviceModeScreenSettings, 0, sizeof(DEVMODE));
		DeviceModeScreenSettings.dmSize = sizeof(DEVMODE);
		DeviceModeScreenSettings.dmPelsWidth = Width;
		DeviceModeScreenSettings.dmPelsHeight = Height;
		DeviceModeScreenSettings.dmBitsPerPel = Bits;
		DeviceModeScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSHEIGHT | DM_PELSWIDTH;

		if (ChangeDisplaySettings(&DeviceModeScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
			if (MessageBox(NULL, L"Full Window Failed. Windowed Mode?", L"Maybe", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
				FullScreen = 0;
			else
				throw - 1;
		}
	}

	if (FullScreen) {
		dwExtendedStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(0);
	}
	else {
		dwExtendedStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	RECT WindowRect;
	WindowRect.left = 1;
	WindowRect.top = 1;
	WindowRect.right = (long)Width;
	WindowRect.bottom = (long)Height;

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExtendedStyle);

	this->hWindowHand = CreateWindowEx(
		dwExtendedStyle,
		ClassName,
		Title,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle,
		0, 0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top,
		0, 0,
		this->hInstance,
		0);

	if (!this->hWindowHand) {
		this->DestroyThisWindow();
		MessageBox(0, L"Window Couldnt Created!", L"Errorü", MB_OK | MB_ICONEXCLAMATION);
		goto end;
	}

	this->hDeviceContext = GetDC(this->hWindowHand);
	if (!this->hDeviceContext) {
		this->DestroyThisWindow();
		MessageBox(0, L"Couldnt Get Device Context!", L"Errorü", MB_OK | MB_ICONEXCLAMATION);
		goto end;
	}

	SetWindowLongPtr(this->hWindowHand, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow(this->hWindowHand, SW_SHOW);
	SetForegroundWindow(this->hWindowHand);
	SetFocus(this->hWindowHand);


	this->ClassName = ClassName;

	this->ResX = Width;
	this->ResY = Height;
	this->Bits = Bits;
end:
	;
}

LRESULT CALLBACK Window::Window::WndProc(HWND hWnd, UINT uMessage, WPARAM wParameter, LPARAM lParameter) {
	Window* currentWindow = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	switch (uMessage)
	{
	case WM_QUIT:
		currentWindow->ShouldQUit = 1;
		break;
	case WM_ACTIVATE:
		if (!HIWORD(wParameter))
			currentWindow->WindowActive = TRUE;
		else
			currentWindow->WindowActive = FALSE;
		break;
	case WM_SYSCOMMAND:
		switch (wParameter)
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
		default:
			break;
		}

	case WM_CLOSE:
		PostQuitMessage(0);
		currentWindow->ShouldQUit = 1;
		break;

	case WM_KEYDOWN:
		currentWindow->keys[wParameter] = TRUE;
		break;

	case WM_KEYUP:
		currentWindow->keys[wParameter] = FALSE;
		break;

	case WM_SIZE:
		//currentWindow->FixedResizeFunction(LOWORD(lParameter), HIWORD(lParameter));
		return 1;
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParameter, lParameter);
	}
	return 0;

}

int Window::Window::PoolMessages() {
	MSG message;
	if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
		return 1;
	}
	return 0;
}

void Window::Window::DestroyThisWindow() {
	if (FullScreen) {
		ChangeDisplaySettings(0, 0);
		ShowCursor(1);
	}

	if (this->hDeviceContext && !ReleaseDC(this->hWindowHand, this->hDeviceContext)) {
		MessageBox(0, L"Couldnt Relase Device Context", L"Errorü", MB_OK | MB_ICONEXCLAMATION);
		this->hDeviceContext = 0;
	}

	if (this->hWindowHand && !DestroyWindow(this->hWindowHand)) {
		MessageBox(0, L"Couldnt Destroy Window", L"Errorü", MB_OK | MB_ICONEXCLAMATION);
		this->hWindowHand = 0;
	}

	if (!UnregisterClass(this->ClassName, this->hInstance)) {
		MessageBox(0, L"Couldnt Unregister Class", L"Errorü", MB_OK | MB_ICONEXCLAMATION);
		this->hInstance = 0;
	}
}
