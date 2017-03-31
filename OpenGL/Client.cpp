#include "Client.h"

Client::Client() {
}

Client::~Client() {
}

void Client::Update() {
	ImGui::Begin("Raknet Settings");
	ImGui::Combo("User Type", &m_type, "User\0Host");
	
	if(m_type == (int)USER_TYPE::USER) {
		ImGui::InputText("IP", m_user.ip, 25);
		ImGui::InputInt("Port", &m_user.port);
		ImGui::Button("Connect to IP"); ImGui::SameLine();
		ImGui::Button("Disconnect");
	} else if(m_type == (int)USER_TYPE::HOST) {
		ImGui::InputText("Server Name", m_host.serverName, 16);
		ImGui::Button("Start Server");
	}

	// CONSOLE
	ImGui::ListBoxHeader("Console");
	{
		// Get Server messages
		for(int i = 0; i < 5; i++) {
			ImGui::Text(std::string("Hello %i").c_str());
		}
		ImGui::ListBoxFooter();
	}

	ImGui::InputText("", m_talkBuffer, 30); ImGui::SameLine();
	ImGui::Button("Send");

	ImGui::End();
}

void Client::HandleNetworkConnection() {
	m_pPeerInterface = RakNet::RakPeerInterface::GetInstance();
	InitaiseClientConnection();
}

void Client::InitaiseClientConnection() {
	RakNet::SocketDescriptor sd;

	m_pPeerInterface->Startup(1, &sd, 1);

	// Attempting Connection;

	RakNet::ConnectionAttemptResult res = m_pPeerInterface->Connect(m_user.ip, m_user.port, nullptr, 0);

	if(res != RakNet::CONNECTION_ATTEMPT_STARTED) {
		// Unable to start connection error number (res)
	}
}

void Client::HandleNetworkMessages() {
	RakNet::Packet* packet;

	for(packet = m_pPeerInterface->Receive(); packet; m_pPeerInterface->DeallocatePacket(packet), packet = m_pPeerInterface->Receive()) {
		switch(packet->data[0]) {
		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
			// Another Client has disconnected
			break;
		case ID_REMOTE_CONNECTION_LOST:
			// Another client has lost cnonnection
			break;
		case ID_REMOTE_NEW_INCOMING_CONNECTION:
			// Another client connected
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
			// out connection request has been accepted
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			// the server is full
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			// we have been disconnected
			break;
		case ID_CONNECTION_LOST:
			// lost connection
			break;
		default:
			// Unknown ID
			break;
		}
	}
}
