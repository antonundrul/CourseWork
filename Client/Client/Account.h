#pragma once
#include <iostream>
#include <string>
#include <iomanip>

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

using namespace std;

class Account {
private:
	int ID;
	string login;
	string password;
public:
	Account();
	Account(const Account& obj);
	void setLogin(string login);
	string getLogin();
	void setPassword(string Password);
	string getPassword();
	void setId(int Id);
	int getId();

	void addAcc(SOCKET sock,int id);
	//void edit(SOCKET sock);
	void viewAcc(SOCKET sock);
	void removeAcc(SOCKET sock);
	void deleteAllAcc(SOCKET sock);
	int authorization(SOCKET sock,int id);

	friend istream& operator >> (istream& input, Account& obj);
	friend ostream& operator << (ostream& output, Account& obj);
};