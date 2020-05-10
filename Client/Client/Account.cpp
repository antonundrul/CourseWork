#include"Account.h"
#include "Text.h"

Account::Account() {
	this->login = "";
	this->password = "";
	this->ID = 0;
}
Account::Account(const Account& obj) {
	this->ID = obj.ID;
	this->login = obj.login;
	this->password = obj.password;
}
void Account::setLogin(string login) {
	this->login = login;
}

string Account::getLogin() {
	return this->login;
}

void Account::setPassword(string Password) {
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

//void Account::inputLogin()
//{
//	string login;
//	cout << "  �����: ";
//	cin >> login;
//	this->setLogin(login);
//}
//
//void Account::inputPassword()
//{
//	cout << "  ������: ";
//	cin >> this->password;// = Validation<int>::getPassword(login, message);
//
//}


istream& operator >> (istream& input, Account& obj) {

	input >> obj.ID;
	getline(input, obj.login);
	getline(input, obj.password);
	return input;
}

ostream& operator << (ostream& output, Account& obj) {
	output << obj.ID << "\t" << obj.login << "\t" << obj.password << "\n";
	return output;
}



void Account::addAcc(SOCKET sock, int id) {


	string login, password;
	Account* account = new Account();

	cout << "�����: ";
	cin >> login;
	send(sock, login.c_str(), 50, 0);

	char  checkBuf[50];
	int check;

	recv(sock, checkBuf, sizeof(checkBuf), 0);
	check = atoi(checkBuf);

	if (check == 1) {
		cout << "������������ � ������� " << login << " ��� ����������." << endl;
		system("pause");
	}
	if (check == 0) {
		cout << "������: ";
		cin >> password;
		send(sock, password.c_str(), 50, 0);
		account->setId(id);
		account->setLogin(login);
		account->setPassword(password);

		cout << "������� " << login << " ��������." << endl;
		system("pause");
	}
}




void Account::viewAcc(SOCKET sock) {
	system("cls");
	cout << " _______________________________________________" << endl;
	cout << setw(10)<<"|      ���:     "<<"|"<<"   �����:      " << setw(15) << "|    ������:    |" << endl;
	cout << " _______________________________________________" << endl;
	int num,id;
	char numBuf[256],idBuf[256],loginBuf[256],passwordBuf[256];
	recv(sock, numBuf, sizeof(numBuf), 0);
	num = atoi(numBuf);
	for (int i = 0; i < num; i++) {
		recv(sock, idBuf, sizeof(idBuf), 0);
		id = atoi(idBuf);
		recv(sock, loginBuf, 50, 0);
		recv(sock, passwordBuf, 50, 0);
		if (id == 1) {
			cout << left << "|" << setw(15)<<"�������������"<<"|"<<setw(15) << loginBuf << "|" << setw(15) << passwordBuf << "|" << endl;
			cout << " _______________________________________________" << endl;
		}
		if (id == 0) {
			cout << left << "|" << setw(15) << "������������" << "|" << setw(15) << loginBuf << "|" << setw(15) << passwordBuf << "|" << endl;
			cout << " _______________________________________________" << endl;
		}
	}
	system("pause");
}

void Account::removeAcc(SOCKET sock) {
	this->viewAcc(sock);
	cout << "������� ����� ��������, ������� �� ������ �������:  ";
	string loginBuf;
	cin >> loginBuf;
	send(sock, loginBuf.c_str(), 50, 0);
	char checkBuf[256];
	int check;
	recv(sock, checkBuf, sizeof(checkBuf), 0);
	check = atoi(checkBuf);
	if (check == 0) {
		cout << "�������� � ����� ������� �� ����������." << endl;
	}
	if (check == 1) {
		cout << "������� " << loginBuf << "������� �����." << endl;
	}
	system("pause");
}

void Account::deleteAllAcc(SOCKET sock) {
	cout << "������������ �������." << endl;
	system("pause");
}

int Account::authorization(SOCKET sock, int id) {
	int flag = -1;
	char flagBuf[5];
	string login, password;

	cout << "�����: ";
	cin >> login;
	send(sock, login.c_str(), 50, 0);

	cout << "������: ";
	cin >> password;
	send(sock, password.c_str(), 50, 0);

	recv(sock, flagBuf, sizeof(flagBuf), 0);
	flag = atoi(flagBuf);
	if (flag == 0) {
		cout << " ______________________________________________" << endl;
		cout << "  �������� ����� ��� ������" << endl;
	}
	return flag;
}
	