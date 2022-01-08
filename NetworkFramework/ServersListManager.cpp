#include "ServersListManager.h"
#include "../Database/UtilsDataBase.h"
#include "SockAddr.h"

#include <sstream>
#include "ServersListManager.h"

using std::istringstream;
using std::stringstream;
using std::fstream;
using std::getline;

ServersListManager::ServersListManager()
{
    string dataBasePath = "../../DataBase/servers_addresses.csv";

    saveAddresses(dataBasePath);
}

ServersListManager::~ServersListManager()
{
}

void ServersListManager::saveAddresses(const std::string& dataBasePath)
{
    // Read the text and get its text
    string fileText = UtilsDataBase::getTextFromFile(dataBasePath);
    // delimiter between columns in the text
    char delimiter = ',';

    // convert the text in string stream
    stringstream sstream(fileText);

    // varibles where to save server id and server address for each line/row
    string sRow; // full row
    string serverID; // (short name)
    string serverName; // (full name)
    string serverAddress;  
    string serverUDPPort;
    string serverTCPListenerPort;

    // for knowing what
    int rowNum = 0;

    // split the text in rows
    while (getline(sstream, sRow))
    {
        if (rowNum != 0) // skip the headings of the table
        {
            // convert the string row into string stream so we can split the columns
            istringstream ssRow(sRow);

            // Following the csv format the first column of a row would be the server id,
            // the second column would be the server address and the third would be the number of users(clients) currently connected to that server
            // using get line with the delimiter we get them
            std::getline(ssRow, serverID, delimiter);
            std::getline(ssRow, serverName, delimiter);
            std::getline(ssRow, serverAddress, delimiter);
            std::getline(ssRow, serverUDPPort, delimiter);
            std::getline(ssRow, serverTCPListenerPort, delimiter);

            // save in the array the server address linked to the server id as a key
            infoServers[serverID].name = serverName;
            infoServers[serverID].ipAddr = sf::IpAddress(serverAddress);
            infoServers[serverID].udpPort = stoi(serverUDPPort);
            infoServers[serverID].tcpListenerPort = stoi(serverTCPListenerPort);
        }

        // count the row
        rowNum++;
    }
}

std::vector<string> ServersListManager::getServersList()
{
    // create a list of servers with all the servers name
    vector<string> servers;
    for (auto serverInfo : infoServers)
        servers.push_back(serverInfo.first);

    return servers;
}

ServerInfo ServersListManager::getServerInfoById(string serverId) const
{
    auto server = infoServers.find(serverId);
    if (server != infoServers.end())
    {
        return server->second;
    }
    else
    {
        return ServerInfo();
    }
}