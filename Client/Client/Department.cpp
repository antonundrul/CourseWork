#include"Department.h"

Department::Department() {
	this->id = 0;
	this->name = "";
	this->manager = "";
	this->amountOfEmplyees = 0;
	this->phone = "";
}

Department::Department(int id, string name, string manager, int amountOfEmployees, string phone) {
	this->id = id;
	this->name = name;
	this->manager = manager;
	this->amountOfEmplyees = amountOfEmployees;
	this->phone = phone;
}

void Department::setId(int id) {
	this->id = id;
}

int Department::getId() {
	return this->id;
}

void Department::setName(string name) {
	this->name = name;
}

string Department::getName() {
	return this->name;
}

void Department::setManager(string manager) {
	this->manager = manager;
}

string Department::getManager() {
	return this->manager;
}

void Department::setAmountOfEmployees(int  amountOfEmployees) {
	this->amountOfEmplyees = amountOfEmployees;
}

int Department::getAmountOfEmployees() {
	return this->amountOfEmplyees;
}

void Department::setPhone(string phone) {
	this->phone = phone;
}

string Department::getPhone() {
	return this->phone;
}

istream& operator >> (istream& input, Department& obj) {
	return input;
}

ostream& operator << (ostream& output, Department& obj) {
	return output;
}


void Department::addDep(SOCKET sock) {
	
	Department* department = new Department();
	int id, amountOfEmployees;
	char idBuf[256], amBuf[256];
	string name, manager, phone;
	system("cls");
	cout << "������� ID ������: ";
	cin >> id;
	itoa(id, idBuf, 10);
	send(sock, idBuf, sizeof(idBuf), 0);

	cout << "������� �������� ������: ";
	cin >> name;
	send(sock, name.c_str(),50, 0);

	cout << "������� ������� ����������� �������: ";
	cin >> manager;
	send(sock, manager.c_str(), 50, 0);

	cout << "������� ���������� ����������� � ������: ";
	cin >> amountOfEmployees;
	itoa(amountOfEmployees , amBuf, 10);
	send(sock, amBuf, sizeof(amBuf), 0);

	cout << "������� ������� ������: ";
	cin >> phone;
	send(sock, phone.c_str(), 50, 0);

	cout << "����� " << name << " ��������." << endl;
	system("pause");
	
}


void Department::viewDep(SOCKET sock) {
	system("cls");
	cout << " _____________________________________________________________________________________________" << endl;
	cout << setw(10) << "|   ID:   " << "|" << "    ��������:       " << setw(15) << "|    ����������:     " << setw(15) << "|   ���-�� �����������:   " << setw(15) << "|    �������:   " <<"|"<< endl;
	cout << " _____________________________________________________________________________________________" << endl;
	int num, id;
	char numBuf[256], idBuf[256], amBuf[256],
		nameBuf[256], managerBuf[256], phoneBuf[256];

	recv(sock, numBuf, sizeof(numBuf), 0);
	num = atoi(numBuf);
	for (int i = 0; i < num; i++) {
		recv(sock, idBuf, sizeof(idBuf), 0);
		recv(sock, nameBuf, 50, 0);
		recv(sock, managerBuf, 50, 0);
		recv(sock, amBuf, sizeof(amBuf), 0);
		recv(sock, phoneBuf, 50, 0);

			cout << left << "|" << setw(9) <<idBuf << "|" << setw(20) << nameBuf << "|" << setw(20) << managerBuf << "|" << setw(25) << amBuf << "|" << setw(15) << phoneBuf << "|" << endl;
			cout << " _____________________________________________________________________________________________" << endl;

	}
	system("pause");
}

void Department::removeDep(SOCKET sock) {
	this->viewDep(sock);
	cout << "������� �������� ������, ������� �� ������ �������:  ";
	string nameBuf;
	cin >> nameBuf;
	send(sock, nameBuf.c_str(), 50, 0);
	char checkBuf[256];
	int check;
	recv(sock, checkBuf, sizeof(checkBuf), 0);
	check = atoi(checkBuf);
	if (check == 0) {
		cout << "������ � ����� ��������� �� ����������." << endl;
	}
	if (check == 1) {
		cout << "����� " << nameBuf << "������� �����." << endl;
	}
	system("pause");
}

void Department::deleteAllDep(SOCKET sock) {
	cout << "������ �������." << endl;
	system("pause");
}

void  Department::searchDep(SOCKET sock) {

	cout << "������� �������� ������, ������� �� ������ �����:  ";
	string nameBuf;
	cin >> nameBuf;
	send(sock, nameBuf.c_str(), 50, 0);

	char checkBuf[256];
	int check;
	recv(sock, checkBuf, sizeof(checkBuf), 0);
	check = atoi(checkBuf);
	if (check == 0) {
		cout << "������ � ����� ��������� �� ����������." << endl;
	}
	else {
		for (int i = 0; i < check; i++) {
		
		}
		cout << "����� " << nameBuf << "������� ������." << endl;
	}
	system("pause");
}