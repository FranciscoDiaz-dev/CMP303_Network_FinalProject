#ifndef _UTILS_H
#define _UTILS_H
#pragma once

#include <string>

/*
	Util class which contains a generator of random floats between two numbers
*/

class Utils {

public:
	// constructor
	Utils();
	// destructor
	~Utils();

	//Rounds a float to two decimal places and turns it into a string
	static std::string stringify(float value);
};

#endif // _UTILS_H
