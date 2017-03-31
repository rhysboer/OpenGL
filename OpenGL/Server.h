#pragma once
#include <iostream>
#include <string>

#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"

class Server {
public:
	~Server();
	
	static Server* GetInstance();

	static void CreateServer(const char* serverName, unsigned short port);
	static void JoinServer(const char* ip, int port, const char* name);

	static void HandleNetworkMessages();

	static bool IsServerRunning();
	static void StopServer();
	static void Destroy();

	static void AddMessage(const char* message);

private:
	Server();

	static Server* m_instance;
	RakNet::RakPeerInterface* m_pPeerInterface;

	unsigned short m_port;
	bool m_running;
	char* m_serverName;
};

