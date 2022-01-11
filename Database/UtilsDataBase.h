#ifndef _UTILS_DATABASE_H
#define _UTILS_DATABASE_H
#pragma once

// Utils DataBase
// It is used for reading from the database (excel file)
// where the servers info are saved

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
