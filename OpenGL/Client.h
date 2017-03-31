#pragma once
#include "imgui.h"


enum class USER_TYPE {
	USER = 0, HOST = 1
};

class Client {
public:
	Client();
	~Client();

	void Update();

private:

	int m_user = (int)USER_TYPE::USER;
	int m_port = 0;
	char m_ip[25] = "0.0.0.0";
};

