#include <iostream>
#include <string>
#include <iomanip>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#include <vector>
#include "Account.h"
#include "Text.h"
#include "functions.h"


using namespace std;

vector <string> vecAlternatives;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		cout << "Error" << endl;
		exit(1);
	}

	sockaddr_in addr;
	int sizeofAddr = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1280);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		cout << "Ошибка: не удалось подключиться к серверу." << endl;
		return 1;
	}
	cout << "Соединение с сервером установлено.\n" << endl;


	Account* account = NULL;
	int k = 0;
	do {
		mainMenu();
		int choice;
		cin >> choice;
		char msg[256];
		itoa(choice, msg, 10);
		send(Connection, msg, sizeof(msg), 0);
		int ch = 0, flag = -1;
		char flagBuf[5];
		string login, password;
		account = new Account();
			char chAdBuf[256], chUsBuf[256];
		switch (choice) {
		case 1:

			system("cls");

			cout << "  ___________________________________________ " << endl;
			cout << " |         Авторизация администратора        |" << endl;
			cout << " |___________________________________________|" << endl;
			recv(Connection, chAdBuf, sizeof(chAdBuf), 0);
			if (atoi(chAdBuf) == 0) {
				cout << "  Администратор не зарегестрирован." << endl << "  Регистрация администратора." << endl;
				cout << " |___________________________________________|" << endl;

				account->addAcc(Connection,1);
			}
			else if (atoi(chAdBuf) == 1 && account->authorization(Connection, 1)==1) {
				
				adminFunctions(Connection);
			}
			system("pause");
			break;
		case 2:
			system("cls");

			cout << "  ___________________________________________ " << endl;
			cout << " |         Авторизация пользователя          |" << endl;
			cout << " |___________________________________________|" << endl;

			
			recv(Connection, chUsBuf, sizeof(chUsBuf), 0);
			if (atoi(chUsBuf) == 0) {
				cout << "  Администратор пока не добавил пользователей." << endl;
				cout << " |___________________________________________|" << endl;
				system("pause");
			}

			else if (atoi(chUsBuf) == 1 && account->authorization(Connection, 0) == 1) {
				
				userFunctions(Connection);
			}
			break;
		case 0:
			k = 1;
			break;
		}
	} while (k == 0);

	system("pause");
	return 0;
}

//	while (true)
//	{
//		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
//		// указание адреса и порта сервера
//		sockaddr_in dest_addr;
//		dest_addr.sin_family = AF_INET;
//		dest_addr.sin_port = htons(1280);
//		dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//		connect(s, (sockaddr*)&dest_addr, sizeof(dest_addr));
//
//		char buf[100], len[100], count[100];
//
//		cout << "\nEnter the string: ";
//		fgets(buf, sizeof(buf), stdin);
//		send(s, buf, 100, 0);
//
//		if (recv(s, len, sizeof(len), 0) != 0) {
//			len[strlen(len)] = '\0';
//			cout << "Length of string: " << len << endl;
//		}
//		if (recv(s, buf, sizeof(buf), 0) != 0)
//		{
//			buf[strlen(buf)] = '\0';
//			cout << "Result string: " << buf << endl;
//		}
//		if (recv(s, count, sizeof(count), 0) != 0) {
//			//count[strlen(count)] = '\0';
//			cout << "Number of deletions: " << count << endl;
//		}
//		closesocket(s);
//	}
//	_getch();
//	WSACleanup();
//	return 0;
//
//
//
//
//	
//
//	WSADATA wsaData;
//	WSAStartup(MAKEWORD(2, 2), &wsaData);
//
//	sockaddr_in addrServer;
//	int sizeOfAddrServer = sizeof(addrServer);
//	addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
//	addrServer.sin_family = AF_INET;
//	addrServer.sin_port = htons(1280);
//
//	SOCKET s = socket(AF_INET, SOCK_STREAM, NULL);
//
//	connect(s, (SOCKADDR*)&addrServer, sizeof(addrServer));
//
//	int choice = -1;
//	while (choice != 0)
//	{
//		cout << "МЕНЮ" << endl;
//		cout << "1. Авторизация" << endl;
//		cout << "2. Регистрация" << endl;
//		cout << "3. Выход" << endl;
//		cout << "Сделайте выбор: "; 
//		cin >> choice;
//		send(s, (char*)&choice, sizeof(choice), NULL);
//
//		system("cls");
//		switch (choice)
//		{
//		case 1:
//		{
//			TypeAccount type;
//			Account* account = nullptr;
//			int idUser = AccountManager::logIn(s, type);
//			system("cls");
//			switch (idUser)
//			{
//			case 0:
//			{
//				account = new Account();
//				account->recvAccount(s);
//				account->menuAdmin(s);
//				delete account;
//			}
//			break;
//
//			case -1:
//				break;
//
//			default:
//			{
//				switch (type)
//				{
//				case ACCOUNT:
//					account = new Account();
//					break;
//				case EXPERT:
//					account = new Expert();
//					break;
//				}
//				account->recvAccount(s);
//				account->menuUser(s);
//				delete account;
//			}
//			break;
//			}
//		}
//		system("cls");
//		break;
//
//		case 2:
//			AccountManager::addUser(s);
//			system("cls");
//			break;
//
//		case 0:
//			break;
//
//		default:
//			cout << "Неверный ввод!" << endl << endl;
//			break;
//		}
//	}
//
//	closesocket(s);
//	WSACleanup();
//	return 0;
//}