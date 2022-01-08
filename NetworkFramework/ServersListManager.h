#ifndef _SERVERS_LIST_MANAGER_H
#define _SERVERS_LIST_MANAGER_H
#pragma once

#include <map>
#include <string>
#include <vector>

#include "ServerInfo.h"

using std::string; using std::map; using std::vector;

class ServersListManager
{
public:
	// constructor
	ServersListManager();
	// destructor
	~ServersListManager();

	// return the collection of addresses of each server
	map<string, ServerInfo> getServersAddresses() { return infoServers; };

	// return a list with all the servers ids
	vector<string> getServersList();

	// return the server info by its id
	ServerInfo getServerInfoById(string serverId) const;

private:
	// Component where the data/info for each server is saved
	// string is the Id of the server
	map<string, ServerInfo> infoServers;

	// Save each server address into the map
	void saveAddresses(const std::string& dataBasePath);
};

#endif //_SERVERS_LIST_MANAGER_H
