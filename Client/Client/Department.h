#pragma once

#include <iostream>
#include <iomanip>
#include <string>

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

using namespace std;

class Department {
private:
	int id;
	string name;
	string manager; //ну или лучше Employee*
	int amountOfEmplyees;
	string phone;
public:
	Department();
	Department(int id, string name, string manager, int amountOfEmployees, string phone);
	void setId(int id);
	int getId();
	void setName(string name);
	string getName();
	void setManager(string manager);
	string getManager();
	void setAmountOfEmployees(int  amountOfEmployees);
	int getAmountOfEmployees();
	void setPhone(string phone);
	string getPhone();

	void addDep(SOCKET sock);
	//void editDep(SOCKET sock);
	void viewDep(SOCKET sock);
	void removeDep(SOCKET sock);
	void deleteAllDep(SOCKET sock);
	void searchDep(SOCKET sock);
	//void sortDep(SOCKET sock);


	friend istream& operator >> (istream& input, Department& obj);
	friend ostream& operator << (ostream& output, Department& obj);
};