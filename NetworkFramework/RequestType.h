#ifndef _REQUEST_TYPE_H
#define _REQUEST_TYPE_H
#pragma once

// Type of request
// It is useful to identify what type of request is, what the server/client want
// It is mainly used for TCP requests

enum class RequestType
{ 
	NONE = 0,
	JOIN,			// join a game
	UPDATE,			// update a player movement
	EXIT,			// exit the game game
	CONFIRMATION,   // request procesed
	REJECTION,      // request was rejected
};

#endif //_REQUEST_TYPE_H
