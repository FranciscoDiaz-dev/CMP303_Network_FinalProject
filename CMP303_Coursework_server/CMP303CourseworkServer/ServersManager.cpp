#include "ServersManager.h"
#include "Utils.h"

#include <sstream>

using std::istringstream;
using std::stringstream;
using std::fstream;
using std::getline;

ServersManager::ServersManager()
    : serverConnection(nullptr)
{
    string dataBasePath = "DataBase/servers_addresses.csv";

    saveAddresses(dataBasePath);
}

ServersManager::~ServersManager()
{
    deleteServerConnection();
}



void ServersManager::saveAddresses(const std::string& dataBasePath)
{
    // Read the text and get its text
    string fileText = Utils::getTextFromFile(dataBasePath);
    // delimiter between columns in the text
    char delimiter = ',';

    // convert the text in string stream
    stringstream sstream(fileText);

    // varibles where to save server id and server address for each line/row
    string sRow;
    string serverAddress;
    string serverID;
    string serverAvailable;

    // split the text in rows
    while (getline(sstream, sRow))
    {
        // convert the string row into string stream so we can split the columns
        istringstream ssRow(sRow);

        // Following the csv format the first column of a row would be the server id,
        // the second column would be the server address and the third would be the number of users(clients) currently connected to that server
        // using get line with the delimiter we get them
        std::getline(ssRow, serverID, delimiter);
        std::getline(ssRow, serverAddress, delimiter);
        std::getline(ssRow, serverAvailable, delimiter);

        // save in the array the server address linked to the server id as a key
        infoServers[serverID].address = serverAddress;
        infoServers[serverID].available = (bool)stoi(serverAvailable);
    }
}


std::vector<string> ServersManager::getServersList()
{
    // create a list of servers with all the servers name
    vector<string> servers;
    for (auto serverInfo : infoServers)
        servers.push_back(serverInfo.first);

    return servers;
}

bool ServersManager::setSelectedServer(string selectServerName)
{ 
    // Find the server in the list
    auto server = infoServers.find(selectServerName);
    if (server != infoServers.end() && server->second.available == true)
    {
        selectedServerName = selectServerName;
        selectedServerInfo = server->second;
        return createServerConnection();
    }
    else
    {
        return false;
    }
}

bool ServersManager::createServerConnection()
{
    // make sure there was not a connection before
    deleteServerConnection();

    serverConnection = new ServerConnection(selectedServerInfo.address, 4444);

    return true;
}

void ServersManager::deleteServerConnection()
{
    if (serverConnection != nullptr)
    {
        delete serverConnection;
        serverConnection = nullptr;
    }
}
