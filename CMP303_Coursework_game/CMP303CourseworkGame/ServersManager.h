#ifndef _SERVERS_MANAGER_H
#define _SERVERS_MANAGER_H
#pragma once

#include <map>
#include <string>
#include <vector>

#include "../../NetworkFramework/ServerInfo.h"

using std::string; using std::map; using std::vector;

class ServersManager
{
public:
	// constructor
	ServersManager();
	// destructor
	~ServersManager();

	// return the collection of addresses for each server
	map<string, ServerInfo> getServersAddresses() { return infoServers; };
	// return a list with all the servers
	vector<string> getServersList();

	ServerInfo getServerInfoById(string serverId) const;

private:
	// Component where the data/info for each server is saved
	map<string, ServerInfo> infoServers;

	// Save each server address into the map
	void saveAddresses(const std::string& dataBasePath);
};

#endif //_SERVERS_MANAGER_H
