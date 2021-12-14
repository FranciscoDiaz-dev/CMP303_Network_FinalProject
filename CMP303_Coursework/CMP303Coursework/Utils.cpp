#include "Utils.h"
#include <sstream>
#include <iomanip>

Utils::Utils()
{
}

Utils::~Utils()
{
}

std::string Utils::stringify(float value)
{
	std::stringstream sStream;
	std::string t;

	sStream << std::fixed << std::setprecision(2) << value;
	sStream >> t;

	return t;
}