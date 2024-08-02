#ifndef _CSTRING_TOOL_EX_
#define _CSTRING_TOOL_EX_

#include <cstringt.h>

//
// CString��CStringA
//
#ifndef CStrT2CStrA
#ifdef _UNICODE
#define CStrT2CStrA(cstr) CStrW2CStrA((cstr))
#else
#define CStrT2CStrA(cstr) (cstr)
#endif
#endif

//
// CString��CStringW
//
#ifndef CStrT2CStrW
#ifdef _UNICODE
#define CStrT2CStrW(cstr) (cstr)
#else
#define CStrT2CStrW(cstr) CStrA2CStrW((cstr))
#endif
#endif

//
// CStringA��CString
//
#ifndef CStrA2CStrT
#ifdef _UNICODE
#define CStrA2CStrT(cstr) CStrA2CStrW((cstr))
#else
#define CStrA2CStrT(cstr) (cstr)
#endif
#endif

//
// CStringW��CString
//
#ifndef CStrW2CStrT
#ifdef _UNICODE
#define CStrW2CStrT(cstr) (cstr)
#else
#define CStrW2CStrT(cstr) CStrW2CStrA((cstr))
#endif
#endif

//
// CStringA��CStringW
//
CStringW CStrA2CStrW(const CStringA &cstrSrcA);

//
// CStringW��CStringA
//
CStringA CStrW2CStrA(const CStringW &cstrSrcW);

//
// COleVariant��CString
// 
CString COleVariantAsCString(COleVariant pVar);
#endif