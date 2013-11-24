#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "GLESAppFramework.h"
#include "eslib/Application.h"
#include <GLES2/gl2.h>
#include <EGL/egl.h>

USING_NS_ESLIB;

typedef struct
{
	/// Window width
	GLint width;

	/// Window height
	GLint height;

	/// Window handle
	EGLNativeWindowType hWnd;

	/// EGL display
	EGLDisplay eglDisplay;

	/// EGL context
	EGLContext eglContext;

	/// EGL surface
	EGLSurface eglSurface;
} ESContext;



LRESULT WINAPI ESWindowProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) 
{
	LRESULT  lRet = 1; 

	switch (uMsg) 
	{ 
	case WM_CREATE:
		break;

	case WM_PAINT:
		{
			ESContext *esContext = (ESContext*)(LONG_PTR) GetWindowLongPtr(hWnd, GWL_USERDATA);

			Application::render();

			eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);

			ValidateRect(esContext->hWnd, NULL);
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CHAR:
		{
			POINT      point;
			ESContext *esContext = (ESContext*)(LONG_PTR) GetWindowLongPtr ( hWnd, GWL_USERDATA );

			GetCursorPos( &point );

			/*if(esContext && esContext->keyFunc)
				esContext->keyFunc(esContext, (unsigned char)wParam, (int)point.x, (int)point.y);*/
		}
		break;

	default:
		lRet = DefWindowProc (hWnd, uMsg, wParam, lParam); 
		break;
	}

	return lRet;
}

GLboolean WinCreate ( ESContext *esContext, const char *title )
{
	WNDCLASS wndclass = {0}; 
	DWORD    wStyle   = 0;
	RECT     windowRect;
	HINSTANCE hInstance = GetModuleHandle(NULL);

	wndclass.style         = CS_OWNDC;
	wndclass.lpfnWndProc   = (WNDPROC)ESWindowProc; 
	wndclass.hInstance     = hInstance; 
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); 
	wndclass.lpszClassName = "opengles2.0"; 

	if (!RegisterClass (&wndclass) ) 
		return FALSE; 

	wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

	// Adjust the window rectangle so that the client area has
	// the correct number of pixels
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = esContext->width;
	windowRect.bottom = esContext->height;

	AdjustWindowRect ( &windowRect, wStyle, FALSE );

	esContext->hWnd = CreateWindow(
		"opengles2.0",
		"",
		wStyle,
		0,
		0,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	SetWindowTextA(esContext->hWnd, title);

	// Set the ESContext* to the GWL_USERDATA so that it is available to the 
	// ESWindowProc
	SetWindowLongPtr (  esContext->hWnd, GWL_USERDATA, (LONG) (LONG_PTR) esContext );

	if(esContext->hWnd==NULL)
		return GL_FALSE;

	ShowWindow(esContext->hWnd, TRUE);

	return GL_TRUE;

}

void WinLoop ( ESContext *esContext )
{
	MSG msg = { 0 };
	int done = 0;
	DWORD lastTime = GetTickCount();

	while (!done)
	{
		int gotMsg = (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0);
		DWORD curTime = GetTickCount();
		float deltaTime = (float)( curTime - lastTime ) / 1000.0f;
		lastTime = curTime;

		if ( gotMsg )
		{
			if (msg.message==WM_QUIT)
			{
				done=1; 
			}
			else
			{
				TranslateMessage(&msg); 
				DispatchMessage(&msg); 
			}
		}
		else
			SendMessage( esContext->hWnd, WM_PAINT, 0, 0 );

		Application::update(deltaTime);
	}
}


///
// CreateEGLContext()
//
//    Creates an EGL rendering context and all associated elements
//
EGLBoolean CreateEGLContext ( EGLNativeWindowType hWnd, EGLDisplay* eglDisplay,
							 EGLContext* eglContext, EGLSurface* eglSurface,
							 EGLint attribList[])
{
	EGLint numConfigs;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLDisplay display;
	EGLContext context;
	EGLSurface surface;
	EGLConfig config;
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

	// get display
	display = eglGetDisplay(GetDC(hWnd));
	if(display==EGL_NO_DISPLAY)
	{
		return EGL_FALSE;
	}

	//Initialize EGL
	if(!eglInitialize(display, &majorVersion, &minorVersion))
	{
		return EGL_FALSE;
	}

	//Get configs num
	if(!eglGetConfigs(display, NULL, 0, &numConfigs))
	{
		return EGL_FALSE;
	}

	//Choose config
	if(!eglChooseConfig(display, attribList, &config, 1, &numConfigs))
	{
		return EGL_FALSE;
	}

	//Create a surface
	surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)hWnd, NULL);
	if(surface==EGL_NO_SURFACE)
	{
		return EGL_FALSE;
	}

	//Create a GL context
	context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
	if(context==EGL_NO_CONTEXT)
	{
		return EGL_FALSE;
	}

	//Make the context current
	if(!eglMakeCurrent(display, surface, surface, context))
	{
		return EGL_FALSE;
	}

	*eglDisplay = display;
	*eglSurface = surface;
	*eglContext = context;

	return EGL_TRUE;
}

GLboolean esCreateWindow(ESContext *esContext, const char* title, GLint width, GLint height, GLuint flags)
{
	EGLint attribList[] =
	{
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_BLUE_SIZE, 5,
		EGL_ALPHA_SIZE, (flags & ES_WINDOW_ALPHA)?8:EGL_DONT_CARE,
		EGL_DEPTH_SIZE, (flags & ES_WINDOW_DEPTH)?8:EGL_DONT_CARE,
		EGL_STENCIL_SIZE, (flags & ES_WINDOW_STENCIL)?8:EGL_DONT_CARE,
		EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE)?1:0,
		EGL_NONE
	};	

	if(esContext==NULL)
	{
		return GL_FALSE;
	}	

	esContext->width = width;
	esContext->height = height;

	if(!WinCreate(esContext, title))
	{
		return GL_FALSE;
	}

	if(!CreateEGLContext(esContext->hWnd,
		&esContext->eglDisplay,
		&esContext->eglContext,
		&esContext->eglSurface,
		attribList))
	{
		return GL_FALSE;
	}	

	return GL_TRUE;
}

void esAppRunLoop()
{
	ESContext esCtx;
	memset(&esCtx, 0, sizeof(ESContext));

	const AppConfig& config = Application::GetConfig();

	esCreateWindow(&esCtx, config.mWindowTitle.c_str(), config.mScreenWidth, config.mScreenHeight, ES_WINDOW_RGB|ES_WINDOW_ALPHA|ES_WINDOW_DEPTH|ES_WINDOW_STENCIL);	

	Application::init();

	WinLoop(&esCtx);

	Application::exit();

}

