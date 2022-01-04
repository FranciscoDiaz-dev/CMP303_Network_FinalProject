#ifndef _SERVERS_MANAGER_H
#define _SERVERS_MANAGER_H
#pragma once

#include <map>
#include <string>
#include <vector>

#include "ServerInfo.h"

using std::string; using std::map; using std::vector;

class ServersManager
{
public:
	// constructor
	ServersManager();
	// destructor
	~ServersManager();

	// return the collection of addresses of each server
	map<string, ServerInfo> getServersAddresses() { return infoServers; };

	// return a list with all the servers ids
	vector<string> getServersList();

	// return the server info by its id
	ServerInfo getServerInfoById(string serverId) const;

	// select the server to use for this game
	void selectServer(string serverId);

	ServerInfo getSelectedServer() { return selectedServerInfo; };

private:
	// Component where the data/info for each server is saved
	// string is the Id of the server
	map<string, ServerInfo> infoServers;

	// Save each server address into the map
	void saveAddresses(const std::string& dataBasePath);

	// the information of the server which has been selected (server being used)
	ServerInfo selectedServerInfo;
};

#endif //_SERVERS_MANAGER_H
