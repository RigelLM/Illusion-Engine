#pragma once
#include <string>

struct StringDataComponent
{
	std::string Data;
	bool NewData = false;

	StringDataComponent() = default;
	StringDataComponent(const StringDataComponent&) = default;
	StringDataComponent(const std::string& data)
		:Data(data) {}

};