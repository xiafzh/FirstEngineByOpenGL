#include "ggl.h"
#include "scene.h"
#include "camera.h"
#include "ggl_def.h"
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glew32.lib")

CScene g_my_scene;

POINT originalPos;
glm::ivec2 old_pos;
bool bRotateView = false;
LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_RBUTTONDOWN:
		originalPos.x = LOWORD(lParam);
		originalPos.y = HIWORD(lParam);
		old_pos = glm::ivec2(originalPos.x, originalPos.y);
		ClientToScreen(hwnd, &originalPos);
		SetCapture(hwnd);
		ShowCursor(false);
		bRotateView = true;
		break;
	case WM_RBUTTONUP:
		bRotateView = false;
		SetCursorPos(originalPos.x, originalPos.y);
		ReleaseCapture();
		ShowCursor(true);
		break;
	case WM_MOUSEMOVE:
		if (bRotateView)
		{
			RECT rect;
			GetWindowRect(hwnd, &rect);
			glm::ivec4 glm_rect = glm::ivec4((int)rect.left, (int)rect.right, (int)rect.top, (int)rect.right);
			glm::ivec2 new_pos = glm::ivec2((int)LOWORD(lParam), (int)HIWORD(lParam));
			g_my_scene.GetCamera()->MouseMove(glm_rect, old_pos, new_pos);
			SetCursorPos(originalPos.x, originalPos.y);
		}
		break;
	case WM_MOUSEWHEEL:
		g_my_scene.GetCamera()->MouseWheel(HIWORD(wParam));
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A':
			g_my_scene.GetCamera()->SetMoveType(EMT_LEFT);
			break;
		case 'D':
			g_my_scene.GetCamera()->SetMoveType(EMT_RIGHT);
			break;
		case 'W':
			g_my_scene.GetCamera()->SetMoveType(EMT_FRONT);
			break;
		case 'S':
			g_my_scene.GetCamera()->SetMoveType(EMT_BACK);
			break;
		}
		break;
	case WM_KEYUP:

		switch (wParam)
		{
		case 'A':
		case 'D':
		case 'W':
		case 'S':
			g_my_scene.GetCamera()->SetMoveType(EMT_INVALID);
			break;
		}
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = NULL;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = GLWindowProc;
	wndclass.lpszClassName = L"GLWindow";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	ATOM atom = RegisterClassEx(&wndclass);
	if (!atom) {
		MessageBox(NULL, L"Register Fail", L"Error", MB_OK);
		return 0;
	}
	RECT rect;
	rect.left = 0;
	rect.right = 1280;
	rect.top = 0;
	rect.bottom = 720;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL);
	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;
	HWND hwnd = CreateWindowEx(NULL, L"GLWindow", L"OpenGL Window", WS_OVERLAPPEDWINDOW,
		100, 100, windowWidth, windowHeight,
		NULL, NULL, hInstance, NULL);
	HDC dc = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormat, &pfd);
	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);
	glewInit();
	g_my_scene.Init();
	g_my_scene.SetViewPortSize(rect.right - rect.left, rect.bottom - rect.top);
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		g_my_scene.Draw();
		SwapBuffers(dc);
	}
	return 0;
}