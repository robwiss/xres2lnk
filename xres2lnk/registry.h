#pragma once
#include <Windows.h>
#include <string>
#include <functional>
#include <exception>

class HKey
{
public:
	// there are lots of ways to make keys so this is kind of a compromise
	// pass a create_hkey function that will set an hkey and return an error code
	// the HKey class encapsulates it and ensures that RegCloseKey is called in the destructor
	HKey(std::function<LONG(PHKEY)> create_hkey);
	virtual ~HKey();

	LONG QueryValue(const std::wstring &valueName, DWORD *value, const DWORD defaultValue);
	LONG QueryValue(const std::wstring &valueName, std::wstring *value, const std::wstring &defaultValue);
private:
	HKEY _hkey;
	bool _own;
};

class KeyError : public std::exception
{
public:
	KeyError(LONG error) : error(error) {}
	virtual ~KeyError() {}

	virtual const char * what() const { return ""; }

	LONG error;
};
