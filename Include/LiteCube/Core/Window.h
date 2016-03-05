/** 
 * @file Window.h
 * @date 05.03.2016
 * @author Ivan Dortulov (ivandortulov@yahoo.com)
 * @brief Contains the declaration of the Window class
 *
 * @section COPYRIGHT
 * Copyright (C) 2016 Ivan Dortulov (ivandortulov@yahoo.com)
 *
 * @section LICENSE 
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef WINDOW_H
#define WINDOW_H

#include "..\LiteDefines.h"

#include <vector>

namespace Lite
{
/**
 * @class Window
 * @brief Class representing an OS window.
 *
 * @example example_window.cpp
 */
class LITE_API Window
{
public:
  /**
   * @enum WindowFlags
   * @brief Flags which control how the window looks and behaves.
   */
  enum WindowFlags
  {
    WF_FULLSCREEN       = 1,                    /**< This is a fullscreen window */
    WF_RESIZABLE        = 1 << 1,               /**< The window can be resized */
    WF_MINIMIZE_BUTTON  = 1 << 2,               /**< The window has a minimize button */ 
    WF_MAXIMIZE_BUTTON  = 1 << 3,               /**< The window has a maximize button */
    WF_MAXIMIZED        = 1 << 4,               /**< The window is initially maximized */ 
    WF_MINIMIZED        = 1 << 5,               /**< The window is initially minimized */
    WF_DEFAULT          = WF_RESIZABLE |        
                          WF_MINIMIZE_BUTTON |
                          WF_MAXIMIZE_BUTTON    /**< Default window style 
                                                (WF_RESIZABLE | WF_MINIMIZE_BUTTON | WF_MAXIMUZE BUTTON). */
  };

public:
  Window();
  virtual ~Window();

public:
  bool Open(int width, int height, 
            const String&  title, int flags = WF_DEFAULT);
  void Close();

  void setSize(int width,  int height);
  void getSize(int& width, int& height) const;

  void setPosition(int x,  int y);
  void getPosition(int& x, int& y) const;

  void setTitle(const String& title);
  String getTitle() const;

  void minimize();
  void restore();

  void hide();
  void show();

  bool isFocused() const;
  bool isCloseRequested() const;

  long handleEvent(void* pEvent);
  void pollEvents(bool all = true);

protected:
  bool registerWindowClass();

protected:
  void* m_handle;
  bool m_isCloseRequested;
  bool m_isCreated;
  bool m_isRegistered;
};

}

#endif