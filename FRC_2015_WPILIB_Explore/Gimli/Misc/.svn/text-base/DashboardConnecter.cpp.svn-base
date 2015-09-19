#include "DashboardConnecter.h"

DashboardConnecter::DashboardConnecter() {
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		return;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1140);
	server_addr.sin_addr.s_addr = inet_addr("10.2.63.5");
}

DashboardConnecter::~DashboardConnecter() {
	close(sock);
}

void DashboardConnecter::SendData() {
	char* temppacket = (char*)malloc(strlen(packet.c_str()));
	strcpy(temppacket, packet.c_str());
	e = sendto(sock, temppacket, strlen(packet.c_str()), 0,
			(struct sockaddr *)&server_addr, sizeof(server_addr));
	packet.clear();
}

void DashboardConnecter::AddData(char* gauge, float toAdd) {
	std::stringstream s_data;

	packet.append(gauge);

	if (!(s_data << toAdd)) {
		return;
	}

	packet.append(s_data.str());
	packet.append("$");
}

void DashboardConnecter::AddData(char* gauge, char* data) {
	packet.append(gauge);
	packet.append(data);
	packet.append("$");
}
