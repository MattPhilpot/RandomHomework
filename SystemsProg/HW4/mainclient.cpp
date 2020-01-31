//Preston Henniger   &&   Matthew Philpot
//3600.001
//Homework 4

//Problem #4

#pragma comment(lib, "ws2_32.lib")

#define WIN32_MEAN_AND_LEAN

#include <winsock2.h>
#include <windows.h>
#include <iostream>

using namespace std;

const int PORT = 4444;
const int BUFFER_LENGTH = 1024;
const char DEF_SERVER_NAME[] = "127.0.0.1";

SOCKET clientSocket = INVALID_SOCKET;

typedef unsigned long IPNumber;
IPNumber FindHostIP(const char *pServerName)
{
	HOSTENT *pHostent;

	// Get hostent structure for hostname:
	if (!(pHostent = gethostbyname(pServerName)))
			return 0;
	
	// Extract primary IP address from hostent structure:
	if (pHostent->h_addr_list && pHostent->h_addr_list[0])
		return *reinterpret_cast<IPNumber*>(pHostent->h_addr_list[0]);
	
	return 0;
}

int main(){
	sockaddr_in	sockAddr;
	WSADATA wsaData;
	int iError = WSAStartup(MAKEWORD(2,2), &wsaData);

	if(iError != NO_ERROR || iError == 1){
        MessageBox(NULL, (LPCTSTR)"Error at WSAStartup()", (LPCTSTR)"Client::Error", MB_OK|MB_ICONERROR);
        WSACleanup();
        return 0;
      }

	if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2){
		MessageBox(NULL, (LPCTSTR)"Error at WSAStartup()", (LPCTSTR)"Client::Error", MB_OK|MB_ICONERROR);
        WSACleanup();
        return 0;
      }

	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(PORT);
	sockAddr.sin_addr.S_un.S_addr = FindHostIP(DEF_SERVER_NAME);

	if((clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET){
		cout << "SOCKET ERROR: Quiting" << endl;
		Sleep(250);
		WSACleanup();
		return 0;
	}

	if (connect(clientSocket, reinterpret_cast<sockaddr*>(&sockAddr), sizeof(sockAddr))!=0){
		cout << "CONNECTION ERROR: Quiting" << endl;
		Sleep(250);
		WSACleanup();
		return 0;
	}
	
	cout << "Type QUIT to quit. Otherwise will send message" << endl;
	while(true){
		char message[BUFFER_LENGTH];
		cin >> message;

		int rec = send(clientSocket,message,sizeof(message),0);
		
		if(rec == -1){
			cout << "SEND ERROR: Quiting" << endl;
			Sleep(250);
			WSACleanup();
			break;
		}

		rec = recv(clientSocket,message,sizeof(message),0);

		if(rec == -1){
			cout << "RECIEVE ERROR: Quiting" << endl;
			Sleep(250);
			WSACleanup();
			break;
		}

		if(strcmp(message,"QUIT") == 0){
			cout << "Quiting" << endl;
			Sleep(250);
			WSACleanup();
			return 0;
		}

		cout << message << endl;

	}

		int rec = send(clientSocket,"QUIT",sizeof("QUIT"),0);
		cout << "Quiting" << endl;
		Sleep(250);
		WSACleanup();

}