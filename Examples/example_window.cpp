/*
 * @file example_window.cpp
 * @author Ivan Dortulov(ivandortulov@yahoo.com)
 *
 * @brief Demonstrates how to use the Window class.
 *
 * @section COPYRIGHT
 * Copyright (C) 2016 Ivan Dortulov (ivandortulov@yahoo.com)
 *
 * @section LICENSE 
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include <LiteCube\Core\Window.h>

using namespace Lite;

int main(int argc, char** argv)
{
  int wndFlags = Window::WF_DEFAULT;

  // If the user passes -fullscreen as an argument, then
  // a fullscreen window will be created.
  if (argc > 1)
  {
    if (strcmp(argv[1], "-fullscreen") == 0)
    {
      wndFlags = Window::WF_FULLSCREEN;
    }
  }

  // Create a new window instance
	Window wnd;
  // Open the window
  if (!wnd.Open(800, 600, L"Hello, World!", wndFlags))
  {
    printf("Error - Unable to open the window!\n");
    exit(-1);
  }

  // By default the window is placed in the center of the screen.
  // Move it to (100, 100).
  wnd.setPosition(100, 100);

  // Until the user closes the window
	while (!wnd.isCloseRequested())
	{
    // Poll window events
		wnd.pollEvents();
	}

  // Close the window. This line is not required, because the
  // window is automatically close when the wnd instance is destroyed.
  wnd.Close();
	return 0;
}