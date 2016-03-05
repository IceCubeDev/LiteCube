/** 
 * @file Window.cpp
 * @date 05.03.2016
 * @author Ivan Dortulov (ivandortulov@yahoo.com)
 * @brief Contains the implementation of the Window class for the Windows OS.
 *
 * @section COPYRIGHT
 * Copyright (C) 2016 Ivan Dortulov (ivandortulov@yahoo.com)
 *
 * @section LICENSE 
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "..\Include\LiteCube\Core\Window.h"
#include <windows.h>

#define WINDOW_CLASS_NAME TEXT("LiteCubeWindow")

#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#define GetWindowText  GetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#define GetWindowText  GetWindowTextA
#endif

namespace Lite
{

static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, 
                                 WPARAM wParam, LPARAM lParam);

/*
 * Platform specific implementation of a structure representing a Window Event.
 */
struct WindowEvent
{
  UINT message;
  LPARAM lParam;
  WPARAM wParam;
};

/**
 * @brief Default constructor.
 *
 * The window is not opened after creating the object.
 * To open the Window you need to call the Open() method.
 * 
 * @see Open()
 */
Window::Window()
  : m_handle(NULL)
  , m_isCloseRequested(false)
  , m_isCreated(false)
  , m_isRegistered(false)
{
}

/**
 * @brief Destructor.
 *
 * The destructor closes the window if it is opened.
 */
Window::~Window()
{
  Close();
}

bool Window::registerWindowClass()
{
  if (!m_isRegistered)
  {
    WNDCLASSEX wcex;
    HINSTANCE  hInstance = GetModuleHandle(NULL);

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = sizeof(Window);
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = WINDOW_CLASS_NAME;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    m_isRegistered = RegisterClassEx(&wcex) != 0;
  }

  return m_isRegistered;
}

/**
 * @brief Open the window.
 *
 * If the window is already opened, this method does nothing.
 *
 * @param[in] width  - width of the window
 * @param[in] height - height of the window
 * @param[in] title  - window title
 * @param[in] flags  - window properties
 *
 * @return true of success, false otherwise
 *
 * @see WindowFlags
 */
bool Window::Open(int width, int height, 
                  const String& title, int flags)
{
  if (!m_isRegistered && !registerWindowClass())
  {
    return false;
  }

  if (!m_isCreated)
  {
    HINSTANCE hInstance = GetModuleHandle(NULL);

    DWORD style   = WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
    DWORD exStyle = WS_EX_OVERLAPPEDWINDOW;

    if (flags & WF_MAXIMIZE_BUTTON)
    {
      style |= WS_MAXIMIZEBOX;
    }
    if (flags & WF_MINIMIZE_BUTTON)
    {
      style |= WS_MINIMIZEBOX;
    }
    if (flags & WF_RESIZABLE)
    {
      style |= WS_THICKFRAME;
      style |= WS_SIZEBOX;
    }
    
    if (flags & WF_FULLSCREEN)
    {
      DEVMODE dmScreenSettings;								                  // Device Mode
		  memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	  // Makes Sure Memory's Cleared
		  dmScreenSettings.dmSize = sizeof(dmScreenSettings);		    // Size Of The Devmode Structure
		  dmScreenSettings.dmPelsWidth	= width;				            // Selected Screen Width
		  dmScreenSettings.dmPelsHeight	= height;				            // Selected Screen Height
		  dmScreenSettings.dmBitsPerPel	= 32;					              // Selected Bits Per Pixel
		  dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		  if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN)
          == DISP_CHANGE_SUCCESSFUL)
      {
        style = WS_POPUP;
        exStyle = WS_EX_APPWINDOW;								
      }
    }

    RECT wndRect;
    wndRect.top = 0;
    wndRect.left = 0;
    wndRect.bottom = height;
    wndRect.right = width;
    AdjustWindowRectEx(&wndRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
    
    m_handle = (void*)CreateWindowEx(
      exStyle,
      WINDOW_CLASS_NAME,
      title.c_str(),
      style,
      CW_USEDEFAULT, CW_USEDEFAULT,
      wndRect.right - wndRect.left, 
      wndRect.bottom - wndRect.top,
      NULL, NULL, hInstance, (LPVOID) this);
  
    if (m_handle == NULL || !IsWindow((HWND) m_handle))
    {
      m_handle = NULL;
      return false;
    }

    ShowWindow((HWND) m_handle, TRUE);
    UpdateWindow((HWND) m_handle);
    m_isCreated = true;
  }

  return m_isCreated;
}

/**
 * @brief Close the window.
 */
void Window::Close()
{
  if (m_handle != NULL && IsWindow((HWND) m_handle))
  {
    CloseWindow((HWND) m_handle);
    m_handle = NULL;
  }
  m_isCreated = false;
}

/**
 * @brief Resize the window.
 * 
 * @param[in] with   - new window width
 * @param[in] height - new window height
 */
void Window::setSize(int width, int height)
{
  if (m_handle != NULL && IsWindow((HWND) m_handle))
  {
    int x, y;
    getPosition(x, y);
    MoveWindow((HWND) m_handle, x, y, width, height, FALSE);
  }
}

/**
 * @brief Obtain the window size.
 *
 * This method returns the entire window size which includes the borders and 
 * title bar.
 *
 * @param[out] width  - the window width
 * @param[out] height - the window height
 */
void Window::getSize(int& width, int& height) const
{
  static RECT rect;
  width = -1;
  height = -1;

  if (m_handle != NULL && IsWindow((HWND) m_handle))
  {
    if (GetWindowRect((HWND) m_handle, &rect))
    {
      width = rect.right - rect.left;
      height = rect.bottom - rect.top;
    }
  }
}

/**
 * @brief Change the window's position.
 *
 * @param[in] x - new x position of the window
 * @param[in] y - new y position of the window
 */
void Window::setPosition(int x, int y)
{
  if (m_handle != NULL && IsWindow((HWND) m_handle))
  {
    int width, height;
    getSize(width, height);
    MoveWindow((HWND) m_handle, x, y, width, height, TRUE);
  }
}

/**
 * @brief Obtain the window's position.
 *
 * @param[out] x - window x position
 * @param[out] y - window y position
 */
void Window::getPosition(int& x, int& y) const
{
  static RECT rect;
  x = -1;
  y = -1;

  if (m_handle != NULL && IsWindow((HWND) m_handle))
  {
    if (GetWindowRect((HWND) m_handle,&rect))
    {
      x = rect.left;
      y = rect.top;
    }
  }
}

/**
 * @brief Set the window's title.
 *
 * @param[in] title - the new window title
 */
void Window::setTitle(const String& title)
{
  if (m_handle != NULL && IsWindow((HWND) m_handle))
  {
    SetWindowText((HWND) m_handle, title.c_str());
  }
}

/**
 * @brief Obtain the window's title.
 *
 * @return The window title
 */
String Window::getTitle() const
{
  if (m_handle != NULL && IsWindow((HWND) m_handle))
  {
    Char title[1024];
    if (GetWindowText((HWND) m_handle, title, sizeof(title)))
    {
      return String(title);
    }
  }

  return String(TEXT(""));
}

/**
 * @brief Minimize the window.
 */
void Window::minimize()
{
  if (m_handle != NULL && IsWindow((HWND) m_handle))
  {
    ShowWindow((HWND) m_handle, SW_MINIMIZE);
  }
}

/**
 * @brief Restore the window if it has been minimized.
 */
void Window::restore()
{
  if (m_handle != NULL && IsWindow((HWND) m_handle))
  {
    ShowWindow((HWND) m_handle, SW_RESTORE);
  }
}

/**
 * @brief Hide the window.
 */
void Window::hide()
{
  if (m_handle != NULL && IsWindow((HWND) m_handle))
  {
    ShowWindow((HWND) m_handle, SW_HIDE);
  }
}

/**
 * @brief Shows the window after it has been hidden.
 */
void Window::show()
{
  if (m_handle != NULL && IsWindow((HWND) m_handle))
  {
    ShowWindow((HWND) m_handle, SW_SHOW);
  }
}

/**
 * @brief Check if the window has input focus.
 *
 * @return true if focused, false otherwise
 */
bool Window::isFocused() const
{
  return (HWND) m_handle == GetFocus();
}

/**
 * @brief Check if the client requested that the window be closed.
 *
 * @return true if the window should close, false otherwise
 */
bool Window::isCloseRequested() const
{
  return m_isCloseRequested;
}

/**
 * @brief Process window events like a resize, move, input and etc..
 *
 * This is an internal helper method and it is not meant to be used outside ot 
 * this class.
 *
 * @param pEvent - pointer to platform specific object that holds the event 
 *                 information
 *
 * @return Platform specific return
 */
long Window::handleEvent(void* pEvent)
{
  WindowEvent* pConvEv = static_cast<WindowEvent*>(pEvent);

  if (pConvEv != NULL)
  {
    switch(pConvEv->message)
    {
    case WM_CLOSE:
      {
        m_isCloseRequested = true;
      }
      break;

    default:
      return 1;
    }
  }

  return 0;
}

/**
 * @brief Poll window events.
 *
 * Poll and process the events in the window's event queue.
 * If the parameter all is set to true, then this method will block until all
 * messages in the queue have been processed.
 *
 * This method need to be called regurarly or the window will hang.
 *
 * @param all - set to true to process all events, currently in the queue
 */
void Window::pollEvents(bool all)
{
  static MSG msg;
  do 
  {
    if (PeekMessage(&msg, (HWND) m_handle, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      break;
    }
  } while(all);
}

static LRESULT CALLBACK WndProc(
  HWND   hWnd, 
  UINT   message, 
  WPARAM wParam, 
  LPARAM lParam)
{
  bool proccesed = false;
  static Window* pWindow = NULL;
  static WindowEvent ev;

  if (message == WM_NCCREATE)
  {
	LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
    pWindow = static_cast<Window*>(lpcs->lpCreateParams);
    SetWindowLongPtr(
      hWnd, GWLP_USERDATA,
      reinterpret_cast<LONG_PTR>(pWindow));
    SetWindowPos(
        hWnd, 0, 0, 0, 0, 0, 
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
  }
  else
  {
    pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
  }

  ev.message = message;
  ev.lParam = lParam;
  ev.wParam = wParam;
  
  if (pWindow != NULL)
  {
    proccesed = pWindow->handleEvent(&ev) == 0;
  }

  if (!proccesed)
  {
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  
  return 0;
}

}