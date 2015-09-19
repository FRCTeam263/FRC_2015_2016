#ifndef DASHBOARDCONNECTER_H
#define DASHBOARDCONNECTER_H

#include "WPILib.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>

class DashboardConnecter {
public:
	DashboardConnecter();
	virtual ~DashboardConnecter();

	void SendData();
	void AddData(char* guage, float toAdd);
	void AddData(char* gauge, char* data);
protected:
private:
	struct sockaddr_in server_addr;
	int sock;
	int e;

	std::string packet;
};

#endif // DASHBOARDCONNECTER_H
