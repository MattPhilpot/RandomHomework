//Preston Henniger   &&   Matthew Philpot
//3600.001
//Homework 4

//Problem #3

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib") 

#include <winsock2.h>
#include <windows.h>
#include <iostream>

using namespace std;

const int PORT = 4444;
const int BUFFER_LENGTH = 1024;

const int clientMax = 3;
int clientCount = 0;

SOCKET serverSocket = INVALID_SOCKET;
SOCKET clientSocket[clientMax];
bool clientsConnected[clientMax];


int main(){
	WSADATA t_wsa;
	WORD wVers = MAKEWORD(2, 2);
    int iError = WSAStartup(wVers, &t_wsa);

	if(iError != NO_ERROR || iError == 1){
        MessageBox(NULL, (LPCTSTR)"Error at WSAStartup()", (LPCTSTR)"Server::Error", MB_OK|MB_ICONERROR);
        WSACleanup();
        return 0;
      }

	if(LOBYTE(t_wsa.wVersion) != 2 || HIBYTE(t_wsa.wVersion) != 2){
		MessageBox(NULL, (LPCTSTR)"Error at WSAStartup()", (LPCTSTR)"Server::Error", MB_OK|MB_ICONERROR);
        WSACleanup();
        return 0;
      }

	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(serverSocket == INVALID_SOCKET || iError == 1){
        MessageBox(NULL, (LPCTSTR)"Invalid Socket!", (LPCTSTR)"Server::Error", MB_OK|MB_ICONERROR);
        WSACleanup();
        return 0;
     }

	SOCKADDR_IN sinServer;
	memset(&sinServer, 0, sizeof(sinServer));
	sinServer.sin_family = AF_INET;
    sinServer.sin_addr.s_addr = INADDR_ANY;
    sinServer.sin_port = htons(PORT);

	if(bind(serverSocket, (LPSOCKADDR)&sinServer, sizeof(sinServer)) == SOCKET_ERROR){
        MessageBox(NULL, (LPCTSTR)"Could not bind the TCP server!", (LPCTSTR)"Server::Error", MB_OK|MB_ICONERROR);
        WSACleanup();
        return 0;
    }

	while(listen(serverSocket, clientMax) == SOCKET_ERROR){
		 MessageBox(NULL, (LPCTSTR)"Could not listen on the TCP server!", (LPCTSTR)"Server::Error", MB_OK|MB_ICONERROR);
        WSACleanup();
        return 0;
	}

	u_long iMode=1;
	ioctlsocket(serverSocket,FIONBIO,&iMode);

	for(int i=0; i<clientMax; i++){
		clientSocket[i] = INVALID_SOCKET;
		clientsConnected[i] = false;
	}

	cout << "Waiting on a client!" << endl;

	bool haveClient = false;

	sockaddr_in sinRemote;
	int nAddrSize = sizeof(sinRemote);
	while(true){

		for(int i=0;i<clientMax;i++){

			if(clientSocket[i] == INVALID_SOCKET)
				continue;

			char message[BUFFER_LENGTH];
			int rec = recv(clientSocket[i],&*message,BUFFER_LENGTH,0);
			if(rec != -1){
				cout << "RECIEVED " << message << endl;
				rec = send(clientSocket[i],message,sizeof(message),0);

				if(strcmp(message,"QUIT") == 0){
					cout << "We had a client quit" << endl;
					closesocket(clientSocket[i]);
					clientSocket[i] = INVALID_SOCKET;
					clientCount--;
				}
			}
		}

		int b = -1;
		for(int i=0; i<clientMax;i++){
			if(clientSocket[i] == INVALID_SOCKET)
				b = i; 
		}

		if(b == -1)
			continue;

		if((clientSocket[b] = accept(serverSocket, (sockaddr*)&sinRemote, &nAddrSize)) != INVALID_SOCKET){
			cout << "Have a new client" << endl;
			iMode=1;
			ioctlsocket(clientSocket[b],FIONBIO,&iMode);
			clientCount++;

			if(clientCount == clientMax)
				cout << "Server is full at the moment" << endl;
		}

	}
	WSACleanup();
}