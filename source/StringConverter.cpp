#include "../headers/StringConverter.h"

std::wstring StringConverter::StringToWide(std::string str)
{
	// take in begin/end iterator of a given string container
	std::wstring wide_string(str.begin(), str.end());
	return wide_string;
}