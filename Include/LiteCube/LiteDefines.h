///////////////////////////////////////////////////////////////////////////////
/// LiteDefines.h -- Contains common definitions
/// 
///  Copyright (C) 2016 Ivan Dortulov (ivandortulov@yahoo.com)
/// 
///  This software may be modified and distributed under the terms
///  of the MIT license.  See the LICENSE file for details.
///////////////////////////////////////////////////////////////////////////////
#ifndef LITEDEFINES_H
#define LITEDEFINES_H

#ifdef LITECUBE_EXPORTS
#define LITE_API __declspec(dllexport)
#else
#define LITE_API __declspec(dllimport)
#endif

#include <string>

namespace Lite
{

static const float EPSILON = 0.0000001f;

#if defined(UNICODE) || defined(_UNICODE)
typedef std::wstring String;
typedef wchar_t      Char;
#else
typedef std::string  String;
typedef char         Char;
#endif

}

#endif // LITEDEFINES_H
