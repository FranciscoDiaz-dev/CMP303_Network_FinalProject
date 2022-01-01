#ifndef _SERVERS_MANAGER_H
#define _SERVERS_MANAGER_H
#pragma once

#include <map>
#include <string>
#include <vector>

#include "ClientConnection.h"

using std::string; using std::map; using std::vector;


struct ServerInfo
{
	// constructor
	ServerInfo() : address(""), available(0) {};

	// components
	string address;
	bool available;
};

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

	// find the selected server name on the list and selected it if it is available
	// return if it has been found and it is available
	bool setSelectedServer(string selectServerName);
	string getSelectedServerName() const { return selectedServerName; };
	ServerInfo getSelectedServerInfo() const { return selectedServerInfo; };

private:
	// Component where the data/info for each server is saved
	map<string, ServerInfo> infoServers;

	// save each server address into the map
	void saveAddresses(const std::string& dataBasePath);

	// Server selected
	string selectedServerName;
	ServerInfo selectedServerInfo;

	ClientConnection connectionToServer;
};

#endif //_SERVERS_MANAGER_H
