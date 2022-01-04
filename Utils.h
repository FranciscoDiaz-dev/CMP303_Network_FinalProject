#ifndef _UTILS_H
#define _UTILS_H
#pragma once

#include <string>

class Utils {

public:
	// constructor
	Utils();
	// destructor
	~Utils();

	// Rounds a float to two decimal places and turns it into a string
	static std::string stringify(float value);

	// Read the csv file from the path and return its content in a string
	static std::string getTextFromFile(const std::string& filePath);
};

#endif // _UTILS_H
