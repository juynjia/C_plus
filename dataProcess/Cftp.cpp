// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "cftp.h"

/////////////////////////////////////////////////////////////////////////////
// CFtpClient

IMPLEMENT_DYNCREATE(CFtpClient, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CFtpClient properties

long CFtpClient::GetAction()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

void CFtpClient::SetAction(long propVal)
{
	SetProperty(0x1, VT_I4, propVal);
}

long CFtpClient::GetFileAction()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

void CFtpClient::SetFileAction(long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}

long CFtpClient::GetTransferType()
{
	long result;
	GetProperty(0x3, VT_I4, (void*)&result);
	return result;
}

void CFtpClient::SetTransferType(long propVal)
{
	SetProperty(0x3, VT_I4, propVal);
}

long CFtpClient::GetTransferMode()
{
	long result;
	GetProperty(0x4, VT_I4, (void*)&result);
	return result;
}

void CFtpClient::SetTransferMode(long propVal)
{
	SetProperty(0x4, VT_I4, propVal);
}

long CFtpClient::GetDirAction()
{
	long result;
	GetProperty(0x5, VT_I4, (void*)&result);
	return result;
}

void CFtpClient::SetDirAction(long propVal)
{
	SetProperty(0x5, VT_I4, propVal);
}

long CFtpClient::GetListType()
{
	long result;
	GetProperty(0x6, VT_I4, (void*)&result);
	return result;
}

void CFtpClient::SetListType(long propVal)
{
	SetProperty(0x6, VT_I4, propVal);
}

short CFtpClient::GetPort()
{
	short result;
	GetProperty(0x7, VT_I2, (void*)&result);
	return result;
}

void CFtpClient::SetPort(short propVal)
{
	SetProperty(0x7, VT_I2, propVal);
}

CString CFtpClient::GetCurrentDir()
{
	CString result;
	GetProperty(0x8, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetCurrentDir(LPCTSTR propVal)
{
	SetProperty(0x8, VT_BSTR, propVal);
}

CString CFtpClient::GetLocalFile()
{
	CString result;
	GetProperty(0x9, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetLocalFile(LPCTSTR propVal)
{
	SetProperty(0x9, VT_BSTR, propVal);
}

CString CFtpClient::GetRemoteFile()
{
	CString result;
	GetProperty(0xa, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetRemoteFile(LPCTSTR propVal)
{
	SetProperty(0xa, VT_BSTR, propVal);
}

CString CFtpClient::GetTarget()
{
	CString result;
	GetProperty(0xb, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetTarget(LPCTSTR propVal)
{
	SetProperty(0xb, VT_BSTR, propVal);
}

CString CFtpClient::GetNewName()
{
	CString result;
	GetProperty(0xc, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetNewName(LPCTSTR propVal)
{
	SetProperty(0xc, VT_BSTR, propVal);
}

CString CFtpClient::GetHost()
{
	CString result;
	GetProperty(0xd, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetHost(LPCTSTR propVal)
{
	SetProperty(0xd, VT_BSTR, propVal);
}

CString CFtpClient::GetUser()
{
	CString result;
	GetProperty(0xe, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetUser(LPCTSTR propVal)
{
	SetProperty(0xe, VT_BSTR, propVal);
}

CString CFtpClient::GetPassword()
{
	CString result;
	GetProperty(0xf, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetPassword(LPCTSTR propVal)
{
	SetProperty(0xf, VT_BSTR, propVal);
}

CString CFtpClient::GetAccount()
{
	CString result;
	GetProperty(0x10, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetAccount(LPCTSTR propVal)
{
	SetProperty(0x10, VT_BSTR, propVal);
}

CString CFtpClient::GetWildcards()
{
	CString result;
	GetProperty(0x11, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetWildcards(LPCTSTR propVal)
{
	SetProperty(0x11, VT_BSTR, propVal);
}

short CFtpClient::GetLastResult()
{
	short result;
	GetProperty(0x12, VT_I2, (void*)&result);
	return result;
}

void CFtpClient::SetLastResult(short propVal)
{
	SetProperty(0x12, VT_I2, propVal);
}

CString CFtpClient::GetQuote()
{
	CString result;
	GetProperty(0x13, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetQuote(LPCTSTR propVal)
{
	SetProperty(0x13, VT_BSTR, propVal);
}

BOOL CFtpClient::GetNotify()
{
	BOOL result;
	GetProperty(0x14, VT_BOOL, (void*)&result);
	return result;
}

void CFtpClient::SetNotify(BOOL propVal)
{
	SetProperty(0x14, VT_BOOL, propVal);
}

CString CFtpClient::GetFirewallServer()
{
	CString result;
	GetProperty(0x2b, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetFirewallServer(LPCTSTR propVal)
{
	SetProperty(0x2b, VT_BSTR, propVal);
}

short CFtpClient::GetFirewallPort()
{
	short result;
	GetProperty(0x2c, VT_I2, (void*)&result);
	return result;
}

void CFtpClient::SetFirewallPort(short propVal)
{
	SetProperty(0x2c, VT_I2, propVal);
}

BOOL CFtpClient::GetPassive()
{
	BOOL result;
	GetProperty(0x2d, VT_BOOL, (void*)&result);
	return result;
}

void CFtpClient::SetPassive(BOOL propVal)
{
	SetProperty(0x2d, VT_BOOL, propVal);
}

BOOL CFtpClient::GetUseVariant()
{
	BOOL result;
	GetProperty(0x30, VT_BOOL, (void*)&result);
	return result;
}

void CFtpClient::SetUseVariant(BOOL propVal)
{
	SetProperty(0x30, VT_BOOL, propVal);
}

long CFtpClient::GetId()
{
	long result;
	GetProperty(0x33, VT_I4, (void*)&result);
	return result;
}

void CFtpClient::SetId(long propVal)
{
	SetProperty(0x33, VT_I4, propVal);
}

long CFtpClient::GetRemoteId()
{
	long result;
	GetProperty(0x34, VT_I4, (void*)&result);
	return result;
}

void CFtpClient::SetRemoteId(long propVal)
{
	SetProperty(0x34, VT_I4, propVal);
}

BOOL CFtpClient::GetUseProperty()
{
	short result;
	GetProperty(0x37, VT_BOOL, (void*)&result);
	return result;
}

void CFtpClient::SetUseProperty(BOOL propVal)
{
	SetProperty(0x37, VT_BOOL, propVal);
}

CString CFtpClient::GetSendData()
{
	CString result;
	GetProperty(0x38, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetSendData(LPCTSTR propVal)
{
	SetProperty(0x38, VT_BSTR, propVal);
}

CString CFtpClient::GetProxyHost()
{
	CString result;
	GetProperty(0x39, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetProxyHost(LPCTSTR propVal)
{
	SetProperty(0x39, VT_BSTR, propVal);
}

CString CFtpClient::GetProxyUser()
{
	CString result;
	GetProperty(0x3A, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetProxyUser(LPCTSTR propVal)
{
	SetProperty(0x3A, VT_BSTR, propVal);
}

CString CFtpClient::GetProxyPassword()
{
	CString result;
	GetProperty(0x3B, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetProxyPassword(LPCTSTR propVal)
{
	SetProperty(0x3B, VT_BSTR, propVal);
}

short CFtpClient::GetProxyPort()
{
	short result;
	GetProperty(0x3C, VT_I2, (void*)&result);
	return result;
}

void CFtpClient::SetProxyPort(short propVal)
{
	SetProperty(0x3C, VT_I2, propVal);
}

short CFtpClient::GetProxyType()
{
	short result;
	GetProperty(0x3D, VT_I2, (void*)&result);
	return result;
}

void CFtpClient::SetProxyType(short propVal)
{
	SetProperty(0x3D, VT_I2, propVal);
}

short CFtpClient::GetHostType()
{
	short result;
	GetProperty(0x3E, VT_I2, (void*)&result);
	return result;
}

void CFtpClient::SetHostType(short propVal)
{
	SetProperty(0x3E, VT_I2, propVal);
}

short CFtpClient::GetTransmissionMode()
{
	short result;
	GetProperty(0x3F, VT_I2, (void*)&result);
	return result;
}

void CFtpClient::SetTransmissionMode(short propVal)
{
	SetProperty(0x3F, VT_I2, propVal);
}



short CFtpClient::GetBlockSize()
{
	short result;
	GetProperty(0x41, VT_I2, (void*)&result);
	return result;
}

void CFtpClient::SetBlockSize(short propVal)
{
	SetProperty(0x41, VT_I2, propVal);
}

short CFtpClient::GetMarkerFrequency()
{
	short result;
	GetProperty(0x42, VT_I2, (void*)&result);
	return result;
}

void CFtpClient::SetMarkerFrequency(short propVal)
{
	SetProperty(0x42, VT_I2, propVal);
}

short CFtpClient::GetRetryCount()
{
	short result;
	GetProperty(0x43, VT_I2, (void*)&result);
	return result;
}

void CFtpClient::SetRetryCount(short propVal)
{
	SetProperty(0x43, VT_I2, propVal);
}


CString CFtpClient::GetCurrentDirExt()
{
	CString result;
	GetProperty(0x44, VT_BSTR, (void*)&result);
	return result;
}

void CFtpClient::SetCurrentDirExt(LPCTSTR propVal)
{
	SetProperty(0x44, VT_BSTR, propVal);
}
/////////////////////////////////////////////////////////////////////////////
// CFtpClient operations

BOOL CFtpClient::Connect(LPCTSTR Host, LPCTSTR User, LPCTSTR Password, LPCTSTR Account)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Host, User, Password, Account);
	return result;
}

BOOL CFtpClient::Disconnect()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CFtpClient::Abort()
{
	BOOL result;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CFtpClient::AbortFile()
{
	BOOL result;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CFtpClient::DeleteFile(LPCTSTR Target)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Target);
	return result;
}

BOOL CFtpClient::GetFile(LPCTSTR RemoteFile, LPCTSTR LocalFile)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		RemoteFile, LocalFile);
	return result;
}

BOOL CFtpClient::PutFile(LPCTSTR LocalFile, LPCTSTR RemoteFile)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		LocalFile, RemoteFile);
	return result;
}

BOOL CFtpClient::AppendFile(LPCTSTR LocalFile, LPCTSTR RemoteFile)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		LocalFile, RemoteFile);
	return result;
}

BOOL CFtpClient::RenameFile(LPCTSTR Target, LPCTSTR NewName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Target, NewName);
	return result;
}

BOOL CFtpClient::ShortList()
{
	BOOL result;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CFtpClient::LongList()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CFtpClient::Ascii()
{
	BOOL result;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CFtpClient::Binary()
{
	BOOL result;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CFtpClient::FileMode()
{
	BOOL result;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CFtpClient::EventMode()
{
	BOOL result;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CFtpClient::ListDir(LPCTSTR Wildcards)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x24, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Wildcards);
	return result;
}

BOOL CFtpClient::AbortDir()
{
	BOOL result;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CFtpClient::ChangeDir(LPCTSTR Target)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Target);
	return result;
}

BOOL CFtpClient::ParentDir()
{
	BOOL result;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CFtpClient::RenameDir(LPCTSTR Target, LPCTSTR NewName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Target, NewName);
	return result;
}

BOOL CFtpClient::CreateDir(LPCTSTR Target)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Target);
	return result;
}

BOOL CFtpClient::RemoveDir(LPCTSTR Target)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Target);
	return result;
}

BOOL CFtpClient::FwConnect(LPCTSTR FwServer, short FwPort, LPCTSTR Host, LPCTSTR User, LPCTSTR Password, LPCTSTR Account)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_I2 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		FwServer, FwPort, Host, User, Password, Account);
	return result;
}

BOOL CFtpClient::Cancel()
{
	BOOL result;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CFtpClient::ReceiveB(const VARIANT& Buffer, long Bytes)
{
	long result;
	static BYTE parms[] =
		VTS_VARIANT VTS_I4;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		&Buffer, Bytes);
	return result;
}

BOOL CFtpClient::SendB(const VARIANT& Buffer, long Bytes)
{
	BOOL result;
	static BYTE parms[] =
		VTS_VARIANT VTS_I4;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		&Buffer, Bytes);
	return result;
}

BOOL CFtpClient::Remote(long RemoteId, LPCTSTR SrcFile, LPCTSTR DestFile)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR;
	InvokeHelper(0x35, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		RemoteId, SrcFile, DestFile);
	return result;
}

BOOL CFtpClient::RemoteAppend(long RemoteId, LPCTSTR SrcFile, LPCTSTR DestFile)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR;
	InvokeHelper(0x36, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		RemoteId, SrcFile, DestFile);
	return result;
}

void CFtpClient::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CFtpClient::Parse(LPCTSTR ListLine, short* IsDir, BSTR* Name, long* Size, BSTR* DateTime, BSTR* Permissions)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_PI2 VTS_PBSTR VTS_PI4 VTS_PBSTR VTS_PBSTR;
	InvokeHelper(0x40, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		ListLine, IsDir, Name, Size, DateTime, Permissions);
	return result;
}

BOOL CFtpClient::Allocate(short Bytes)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x45, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Bytes);
	return result;
}

BOOL CFtpClient::Reinit()
{
	BOOL result;
	InvokeHelper(0x46, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}



BOOL CFtpClient::PutUniqueFile(LPCTSTR LocalFile, LPCTSTR RemoteFile)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x47, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		LocalFile, RemoteFile);
	return result;
}

BOOL CFtpClient::GetFileWithRestart(LPCTSTR RemoteFile, LPCTSTR LocalFile,
                                    LPCTSTR Marker)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x48, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		RemoteFile, LocalFile, Marker);
	return result;
}

BOOL CFtpClient::PutFileWithRestart(LPCTSTR LocalFile, LPCTSTR RemoteFile, 
                                    LPCTSTR Marker)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x49, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		LocalFile, RemoteFile, Marker);
	return result;
}

BOOL CFtpClient::GetMultipleFile(LPCTSTR LocalDir, LPCTSTR Remote, 
                                    BOOL Recursive)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BOOL;
	InvokeHelper(0x4A, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		LocalDir, Remote, Recursive);
	return result;
}

BOOL CFtpClient::PutMultipleFile(LPCTSTR Local, LPCTSTR RemoteDir, 
                                    BOOL Recursive)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BOOL;
	InvokeHelper(0x4B, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Local, RemoteDir, Recursive);
	return result;
}

BOOL CFtpClient::BlockMode()
{
	BOOL result;
	InvokeHelper(0x4C, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CFtpClient::StreamMode()
{
	BOOL result;
	InvokeHelper(0x4D, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CFtpClient::Login(LPCTSTR User, LPCTSTR Password, LPCTSTR Account)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR;
	InvokeHelper(0x4E, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		User, Password, Account);
	return result;
}