#include "Client.h"

Client::Client() {
}

Client::~Client() {
}

void Client::Update() {
	ImGui::Begin("Raknet Settings");
	ImGui::Combo("User Type", &m_user, "User\0Host");
	
	if(m_user == (int)USER_TYPE::USER) {
		ImGui::InputText("IP", m_ip, 25);
		ImGui::InputInt("Port", &m_port);
		ImGui::Button("Connect to IP");
	} else if(m_user == (int)USER_TYPE::HOST) {

	}

	ImGui::End();
}
