#ifndef _UTILS_DATABASE_H
#define _UTILS_DATABASE_H
#pragma once

#include <string>

class UtilsDataBase {

public:
	// constructor
	UtilsDataBase();
	// destructor
	~UtilsDataBase();

	// Read the csv file from the path and return its content in a string
	static std::string getTextFromFile(const std::string& filePath);
};

#endif // _UTILS_DATABASE_H
