#include "Server.h"

Server* Server::m_instance = nullptr;


Server::Server() {
	m_running = false;
}

Server::~Server() {
}

Server * Server::GetInstance() {
	if(m_instance == nullptr)
		m_instance = new Server();

	return m_instance;
}

void Server::CreateServer(const char* serverName, unsigned short port) {
	Server* instance = GetInstance();

	instance->m_port = port;
	instance->m_pPeerInterface = RakNet::RakPeerInterface::GetInstance();

	RakNet::SocketDescriptor sd(port, 0);

	instance->m_pPeerInterface->Startup(32, &sd, 1);
	instance->m_pPeerInterface->SetMaximumIncomingConnections(32);

	instance->m_running = true;
}

void Server::HandleNetworkMessages() {
	Server* instance = GetInstance();

	if(IsServerRunning()) {
		RakNet::Packet* packet = nullptr;

		while(true) {
			for(packet = instance->m_pPeerInterface->Receive(); packet; instance->m_pPeerInterface->DeallocatePacket(packet), packet = instance->m_pPeerInterface->Receive()) {
				switch(packet->data[0]) {
				case ID_NEW_INCOMING_CONNECTION:
					// Incoming Connection
					break;
				case ID_DISCONNECTION_NOTIFICATION:
					// A client has disconnected
					break;
				case ID_CONNECTION_LOST:
					// A client lost connection
					break;
				default:
					// Received a message with an unknown id
					packet->data[0];
					break;
				}
			}
		}
	}
}

bool Server::IsServerRunning() {
	return GetInstance()->m_running;
}

void Server::Destroy() {
	if(m_instance != nullptr) {
		delete m_instance;
	}

	m_instance = nullptr;
}
