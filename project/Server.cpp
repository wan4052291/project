#include<iostream>
#include<winsock2.h>
#include<thread>
#include<vector>
#include<string>
#include"DataBase.h"
using namespace std;
using namespace N;
struct passVal {
	SOCKET sock;
	struct sockaddr_in sockaddr;
};

string parseString(char* ch) {
	string str(ch);
	vector<string> token;
	size_t pos = 0;
	const string split = " ";
	string temp = "";
	while ((pos = str.find(split)) != string::npos) {
		temp = str.substr(0, pos);
		cout << temp << endl;
		token.push_back(temp);
		str.erase(0, pos + 1);
	}
	token.push_back(str);
	
	return "";
}

static void RecvThread(struct passVal pass) {
	char buf[1024];
	int rtVal;
	SOCKET sock = pass.sock;
	struct sockaddr_in sockaddr = pass.sockaddr;
	DataBase* db = DataBase::getInstance();
	cout << db->n << endl;
	while (1) {
		memset(buf,0, sizeof(buf));
		int addrlen = sizeof(sockaddr);
		rtVal = recv(sock, buf, sizeof(buf), 0);
		//cout << rtVal << endl;
		if (rtVal < 0) {
			cout << WSAGetLastError() << endl;
			cout << inet_ntoa(sockaddr.sin_addr) << " Disconnected!\n" << endl;
			return;
		}
		buf[rtVal] = '\0';
		cout << buf;
		parseString(buf);
		if (rtVal > 0) {
			send(sock, "Hello World!", sizeof("Hello World!"), 0);
		}
	}
	cout << inet_ntoa(sockaddr.sin_addr) << endl;
}

void SendThread(SOCKET sock, struct sockaddr_in sockaddr) {

}


int main() {
	SOCKET sockfd;
	WSADATA wsd;
	struct sockaddr_in addr;
	int rtVal;
	vector<struct sockaddr_in> clAddr;
	DataBase *db = DataBase::getInstance();
	db->n = 5;
	//init
	rtVal = WSAStartup(MAKEWORD(2,2),&wsd);
	if (rtVal != 0) {
		cout << "Error code : " << WSAGetLastError() << endl;
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == INVALID_SOCKET) {
		cout << "Socket Generate fail!" << endl;
	}
	addr.sin_port = htons((short)8888);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	rtVal = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if (rtVal != 0) {
		cout << "Bind fail!" << endl;
	}
	rtVal = listen(sockfd, 5);
	if (rtVal != 0) {
		cout << "Listen fail!" << endl;
	}

	cout << "Server is running......" << endl;
	//accept connect
	while (1) {
		struct sockaddr_in client;
		SOCKET cSock;
		int addrlen = sizeof(client);
		cSock = accept(sockfd, (struct sockaddr*)&client, &addrlen);
		cout << inet_ntoa(client.sin_addr) << " Connect" << endl;
		struct passVal pass = { cSock,client };
		thread recvthread(RecvThread,pass);
		recvthread.detach();
	}
	closesocket(sockfd);
	return 0;
}