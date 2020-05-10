#include <vector>
#include"Account.h"
#include "Functions.h"


static int timeBlockAdmin = 0;
extern vector<Account*> vecAccount;



Account::Account() {
	this->login = "";
	this->password = "";
	this->ID = 0;
}

Account::Account(const Account&obj) {
	this->login = obj.login;
	this->password = obj.password;
	this->ID = obj.ID;
}

void Account::setLogin(string login) {
	this->login = login;
}

string Account::getLogin() {
	return this->login;
}

void Account::setPassword(string password) {
	this->password = password;
}

string Account::getPassword() {
	return this->password;
}

void Account::setId(int Id) {
	this->ID = Id;
}

int Account::getId() {
	return this->ID;
}


int Account::checkAdmin() {

	Account* account;
	int isFlagAdmin = 0;

	for (int i = 0; i < vecAccount.size();i++) {

		if (vecAccount.at(i)->getId() == 1) {
			isFlagAdmin = 1;
			return 1; 
		}
	}
	if (isFlagAdmin == 0) return 0;
}

int Account::checkUser() {
	Account account;
	int isFlagUser = 0;
	for (int i = 0; i < vecAccount.size(); i++) {
		if (vecAccount.at(i)->getId() == 0) {
			isFlagUser = 1;
			return 1;
		}
	}
	if (isFlagUser == 0) return 0;
}



istream& operator >> (istream& input, Account& obj) {
	
	input >> obj.ID;
	input.get();
	getline(input, obj.login);
	getline(input, obj.password);
	return input;
}

ostream& operator << (ostream& output, Account& obj) {
	output << obj.getId() <<"\n"<<obj.getLogin() << "\n" << obj.getPassword() << "\n";
	return output;
}

void Account::addAcc(SOCKET sock, int id) {
	Account* account = new Account();
	char loginBuf[50], passwordBuf[50], checkBuf[50];
	string login, password;
	int check = 0;
	recv(sock, loginBuf, 50, 0);
	login = string(loginBuf);
	login = encryption(login);
	for (int i = 0; i < vecAccount.size(); i++) {
		if (login == vecAccount.at(i)->getLogin()) {
			check = 1;
			break;
		}
	}
	itoa(check, checkBuf, 10);
	send(sock, checkBuf, sizeof(checkBuf), 0);
	if (check == 1) {
		cout << "Пользователь с логином " << loginBuf << " уже существует." << endl;
	}
	if (check == 0) {
		recv(sock, passwordBuf, 50, 0);
		password = string(passwordBuf);
		password = encryption(password);
		account->setId(id);
		account->setLogin(login);
		account->setPassword(password);
		vecAccount.push_back(account);
		saveAccountFile("Account.txt");
		cout << "Аккаунт " << loginBuf << " добавлен." << endl;
	}
}

int Account::authorization(SOCKET sock, int ID) {
	char loginBuf[50], passwordBuf[50];
	string login, password;
	int flag = 0;
	recv(sock, loginBuf, 50, 0);
	login = string(loginBuf);
	login = encryption(login);
	recv(sock, passwordBuf, 50, 0);
	password = string(passwordBuf);
	password = encryption(password);
	for (int i = 0; i < vecAccount.size(); i++) {
		if (vecAccount.at(i)->getLogin() == login && vecAccount.at(i)->getPassword() == password) {
			flag = 1;
			break;
		}
	}
	char flagBuf[5];
	itoa(flag, flagBuf, 10);
	send(sock, flagBuf, sizeof(flagBuf), 0);
	return flag;
}

void Account::viewAcc(SOCKET sock) {
	string login, password;
	char numBuf[256],idBuf[256], loginBuf[256], passwordBuf[256];
	//recv(sock, numBuf, sizeof(numBuf), 0);
	itoa(vecAccount.size(), numBuf, 10);
	send(sock, numBuf, sizeof(numBuf), 0);
	for (int i = 0; i < vecAccount.size(); i++) {
		itoa(vecAccount.at(i)->getId(), idBuf, 10);
		send(sock, idBuf, sizeof(idBuf), 0);
		login = vecAccount.at(i)->getLogin();
		login = decryption(login);
		send(sock, login.c_str(), 50, 0);
		password = vecAccount.at(i)->getPassword();
		password = decryption(password);
		send(sock, password.c_str(), 50, 0);
	}

}
void Account::removeAcc(SOCKET sock) {
	this->viewAcc(sock);
	char loginBuf[256],checkBuf[256];
	int check = 0;
	string login;
	recv(sock, loginBuf, 50, 0);
	login = string(loginBuf);
	login = encryption(login);
	for (int i = 0; i < vecAccount.size(); i++) {
	
		if (login == vecAccount.at(i)->getLogin()) {
			vecAccount.erase(vecAccount.begin() + i);
			saveAccountFile("Account.txt");
			check++;
		}
	}
	itoa(check, checkBuf, 10);
	send(sock, checkBuf, sizeof(checkBuf), 0);
	if (check == 0) {
		cout << "Аккаунта с таким логином не существует." << endl;
	}
	if (check == 1) {
		cout << "Аккаунт " << loginBuf << "успешно удалён." << endl;
	}
}

void Account::deleteAllAcc(SOCKET sock) {
	for (int i = 0; i < vecAccount.size(); i++) {
		if (vecAccount.at(i)->getId() == 0) {
			vecAccount.erase(vecAccount.begin() + i);
		}
	}
	saveAccountFile("Account.txt");
	cout << "Все пользователи удалены." << endl;
}


