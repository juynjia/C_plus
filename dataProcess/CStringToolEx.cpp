#include "stdafx.h"
#include "CStringToolEx.h"
#include <cstringt.h>

//
// CStringA¬‡CStringW
//
CStringW CStrA2CStrW(const CStringA &cstrSrcA)
{
	int len = MultiByteToWideChar(CP_ACP, 0, LPCSTR(cstrSrcA), -1, NULL, 0);
	wchar_t *wstr = new wchar_t[len];
	memset(wstr, 0, len * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, LPCSTR(cstrSrcA), -1, wstr, len);
	CStringW cstrDestW = wstr;
	delete[] wstr;

	return cstrDestW;
}

//
// CStringW¬‡CStringA
//
CStringA CStrW2CStrA(const CStringW &cstrSrcW)
{
	int len = WideCharToMultiByte(CP_ACP, 0, LPCWSTR(cstrSrcW), -1, NULL, 0, NULL, NULL);
	char *str = new char[len];
	memset(str, 0, len);
	WideCharToMultiByte(CP_ACP, 0, LPCWSTR(cstrSrcW), -1, str, len, NULL, NULL);
	CStringA cstrDestA = str;
	delete[] str;

	return cstrDestA;
}


//
// COleVariant¬‡CString
// 
CString COleVariantAsCString(COleVariant pVar)
{
	CString retval;

	if (pVar.vt == VT_NULL || pVar.vt == VT_EMPTY)
		retval = _T("");
	else
		retval = pVar.bstrVal;

	return retval;
}