#ifndef _REQUEST_TYPE_H
#define _REQUEST_TYPE_H
#pragma once

enum class RequestType
{ 
	NONE = 0,
	JOIN,			// join a game
	UPDATE,			// update a player movement
	EXIT,			// exit the game game
	CONFIRMATION,   // confirmation of received message
	REJECTION,   // confirmation of received message
};

#endif //_REQUEST_TYPE_H
