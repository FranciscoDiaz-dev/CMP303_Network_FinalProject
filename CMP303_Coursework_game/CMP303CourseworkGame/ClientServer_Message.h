#ifndef _CLIENTSERVER_MESSAGE_H
#define _CLIENTSERVER_MESSAGE_H
#pragma once

/*
* Header to contain the Message structure to use between the client-server connection
* This is a plain old data type. This means it is stored in the program simply as a block
* of memory containing all the variables. Which is convenient if we're working with functions
* that send and receive block of memory.
*/

#include <string>

struct ClientServerMessage
{
	std::string playerName;	// the ID number of the game object
	int x, y;		// object position
};

#endif //_CLIENTSERVER_MESSAGE_H


