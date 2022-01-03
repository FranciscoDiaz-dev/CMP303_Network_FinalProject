#ifndef _SERVERS_MANAGER_H
#define _SERVERS_MANAGER_H
#pragma once

#include <map>
#include <string>
#include <vector>

#include "../../NetworkFramework/ServerConnection.h"
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

	// find the server id on the list and selected it if it is available
	// return if it has been found and it is available
	bool initialiseServerById(string serverId);
	bool createServerConnection(ServerInfo& serverInfo);
	string getActiveServerId() const;
	ServerInfo getServerInfoById(string serverId) const;

	// delete the server
	void deleteServerConnection();

	// run the active server
	void runServer();

private:
	// Component where the data/info for each server is saved
	map<string, ServerInfo> infoServers;

	// Save each server address into the map
	void saveAddresses(const std::string& dataBasePath);

	// Server
	ServerConnection* activeServer;
};

#endif //_SERVERS_MANAGER_H
