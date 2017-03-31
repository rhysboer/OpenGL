#include "Server.h"

Server* Server::m_instance = nullptr;


Server::Server() {
	m_console.Create("Server Console", 30, 30);
	m_isOpen = false;
}

Server::~Server() {
}

Server * Server::GetInstance() {
	if(m_instance == nullptr)
		m_instance = new Server();

	return m_instance;
}

void Server::Create() {
	if(m_instance == nullptr) {
		m_instance = new Server();
	}
}

void Server::Destroy() {
	if(m_instance != nullptr)
		delete m_instance;

	m_instance = nullptr;
}

void Server::Print(const char * message) {
	GetInstance()->m_console.printf(message);
}

bool Server::IsOpen() {
	return GetInstance()->m_isOpen;
}
