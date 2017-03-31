#pragma once
#include "imgui.h"
#include "Server.h"

#include "InputManager.h"

enum class USER_TYPE {
	USER = 0, HOST = 1
};

struct HostSettings {
	char serverName[16] = { "MyServer" };
};

struct UserSettings {
	int port = 5456;
	char ip[25] = "127.0.0.1"; // 0.0.0.0
};

class Client {
public:
	Client();
	~Client();

	void Update();

	void HandleNetworkConnection();
	void InitaiseClientConnection();

	void HandleNetworkMessages();

private:

	int m_type = (int)USER_TYPE::USER;
	char m_talkBuffer[30] = "";
	
	HostSettings m_host;
	UserSettings m_user;

	RakNet::RakPeerInterface* m_pPeerInterface;
};

