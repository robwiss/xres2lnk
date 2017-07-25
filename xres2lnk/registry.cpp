#include "registry.h"
#include <Windows.h>
#include <string>
#include <functional>

HKey::HKey(std::function<LONG(PHKEY)> hkey_create)
{
	LONG error = hkey_create(&_hkey);
	if (ERROR_SUCCESS != error)
	{
		throw KeyError(error);
	}
}

HKey::~HKey()
{
	RegCloseKey(_hkey);
}

LONG HKey::QueryValue(const std::wstring &valueName, DWORD *value, const DWORD defaultValue)
{
	*value = defaultValue;
	DWORD bufferSize(sizeof(DWORD));
	DWORD result(0);
	LONG error = ::RegQueryValueExW(_hkey,
		valueName.c_str(),
		0,
		NULL,
		reinterpret_cast<LPBYTE>(&result),
		&bufferSize);
	if (ERROR_SUCCESS == error)
	{
		*value = result;
	}
	return error;
}

LONG HKey::QueryValue(const std::wstring &valueName, std::wstring *value, const std::wstring &defaultValue)
{
	*value = defaultValue;
	WCHAR buf[512];
	DWORD bufferSize = sizeof(buf);
	ULONG error;
	error = RegQueryValueExW(_hkey, valueName.c_str(), 0, NULL, (LPBYTE)buf, &bufferSize);
	if (ERROR_SUCCESS == error)
	{
		*value = buf;
	}
	return error;
}
