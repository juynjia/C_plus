#ifndef _CSTRING_TOOL_EX_
#define _CSTRING_TOOL_EX_

#include <cstringt.h>

//
// CString轉CStringA
//
#ifndef CStrT2CStrA
#ifdef _UNICODE
#define CStrT2CStrA(cstr) CStrW2CStrA((cstr))
#else
#define CStrT2CStrA(cstr) (cstr)
#endif
#endif

//
// CString轉CStringW
//
#ifndef CStrT2CStrW
#ifdef _UNICODE
#define CStrT2CStrW(cstr) (cstr)
#else
#define CStrT2CStrW(cstr) CStrA2CStrW((cstr))
#endif
#endif

//
// CStringA轉CString
//
#ifndef CStrA2CStrT
#ifdef _UNICODE
#define CStrA2CStrT(cstr) CStrA2CStrW((cstr))
#else
#define CStrA2CStrT(cstr) (cstr)
#endif
#endif

//
// CStringW轉CString
//
#ifndef CStrW2CStrT
#ifdef _UNICODE
#define CStrW2CStrT(cstr) (cstr)
#else
#define CStrW2CStrT(cstr) CStrW2CStrA((cstr))
#endif
#endif

//
// CStringA轉CStringW
//
CStringW CStrA2CStrW(const CStringA &cstrSrcA);

//
// CStringW轉CStringA
//
CStringA CStrW2CStrA(const CStringW &cstrSrcW);

//
// COleVariant轉CString
// 
CString COleVariantAsCString(COleVariant pVar);
#endif