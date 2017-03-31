#pragma once
#include <iostream>
#include <string>

#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"

/*
	Enables the use of multiple consoles.
	Source: https://www.codeproject.com/articles/13368/multiple-consoles-for-a-single-application
*/
#include "CConsole\ConsoleLogger.h"

class Server {
public:
	~Server();
	
	static Server* GetInstance();

	static void Create();
	static void Destroy();

	static void Print(const char* message);

	static bool IsOpen();

private:
	Server();
	static Server* m_instance;

	bool m_isOpen = false;
	CConsoleLogger m_console = CConsoleLogger();
};

