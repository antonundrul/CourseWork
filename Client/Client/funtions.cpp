#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "functions.h"
#include"Account.h"
#include"Department.h"
#include "Text.h"

extern vector<string> vecAlternatives;

void adminFunctions(SOCKET sock) {
	int choice;
	char choiceBuf[256];
	int k = 0;
	do {
		adminMenu();
		cin >> choice;
		itoa(choice, choiceBuf, 10);
		send(sock, choiceBuf, sizeof(choiceBuf), 0);
		switch (choice) {
		case 1:
			
			userManageFunctions(sock);
			break;

		case 2:
			
			departmentManageFunctions(sock);

			break;
		case 3: 
			employeesManageMenu();
			break;
			//employeesManageFunctions(sock);
		case 4: 
			solveProblemFunctions(sock);
			break;

		case 0:
			k = 1;
			break;
		}
	} while (k == 0);

}


void userFunctions(SOCKET sock) {
	int choice;
	char choiceBuf[256];
	int k = 0;
	do {
		userMenu();
		cin >> choice;
		itoa(choice, choiceBuf, 10);
		send(sock, choiceBuf, sizeof(choiceBuf), 0);
		switch (choice) {
		case 1:
			break;

		case 2:
			makeChoice(sock);
			break;
		case 0:
			k = 1;
			break;
		}
	} while (k == 0);

}

void userManageFunctions(SOCKET sock) {
	Account* account = new Account();
	int choice;
	char choiceBuf[256];
		int k = 0;
	do {
		userManageMenu();
		cin >> choice;
		itoa(choice, choiceBuf, 10);
		send(sock, choiceBuf, sizeof(choiceBuf), 0);
		switch (choice) {
		case 1:
			account->addAcc(sock, 0);
			break;
		case 2:
			account->viewAcc(sock);
			break;
		case 3:
			account->removeAcc(sock);
			break;
		case 4:
			account->deleteAllAcc(sock);
			break;
		
		case 0: 
			k=1;
			break;
		default: cout << "Введено неверное значение." << endl;
		}
	} while (k == 0);
}

void departmentManageFunctions(SOCKET sock) {
	Department* department = new Department();
	int choice;
	char chBuf[256];
	int k = 0;
	do {
		departmentManageMenu();
	cin >> choice;
	itoa(choice, chBuf, 10);
		send(sock, chBuf, sizeof(chBuf), 0);
		switch (choice) {
		case 1:
			department->addDep(sock);
			break;
		case 2:
			//department->edit(sock);
			break;
		case 3:
			department->viewDep(sock);
			break;
		case 4:
			department->removeDep(sock);
			break;
		case 5:
			department->deleteAllDep(sock);
			break;
		case 6:
			//department->search(sock);
			break;
		case 7:
			//department->sort(sock);
			break;
		case 0:
			k = 1;
			break;
		default:cout << "Введено неверное значение." << endl;
		}
	} while (k == 0);
}


void solveProblemFunctions(SOCKET sock) {
	int choice;
	char chBuf[256];
	int k = 0;
	do {
		solveProblemMenu();
		cin >> choice;
		itoa(choice, chBuf, 10);
		send(sock, chBuf, sizeof(chBuf), 0);
		switch (choice) {
		case 1:
			addAlternatives(sock);
			break;
		case 2:
			viewAlternatives(sock);
			break;
		
		case 0:
			k = 1;
			break;
		default:cout << "Введено неверное значение." << endl;
		}
	} while (k == 0);

}

void addAlternatives(SOCKET sock) {
	string alt;
	int choice, size;
	char chBuf[256], sizeBuf[256];
	int k =0 ;
	do {
		system("cls");
		cout << "Введите альтернативу: ";
		cin.get();
		getline(cin, alt);
		send(sock, alt.c_str(), 200, 0);
		whatElse();
		cin >> choice;
		itoa(choice, chBuf, 10);
		send(sock, chBuf, sizeof(chBuf), 0);
		if (choice == 0) {
			cout << "Введите размер шкалы: ";
			cin >> size;
			itoa(size, sizeBuf, 10);
			send(sock, sizeBuf, sizeof(sizeBuf), 0);
			k = 1;
		}
	} while (k == 0);

}

void viewAlternatives(SOCKET sock) {
	int num;
	char numBuf[256], altBuf[256];
	recv(sock, numBuf, sizeof(numBuf), 0);
	num = atoi(numBuf);
	if (num != 0) {
		system("cls");
		cout << " ___________________________________________________________________________" << endl;
		cout << left << setw(4) << "|№:  " << "|" << setw(70) << "Альтернатива: " << "|" << endl;
		cout << " ___________________________________________________________________________" << endl;
		for (int i = 0; i < num; i++) {

			recv(sock, altBuf, 200, 0);

			cout << left << "|" << setw(4) << i + 1 << "|" << setw(70) << altBuf << "|" << endl;
			cout << " ___________________________________________________________________________" << endl;

		}
	}
	else {
		cout << "Список альтернатив пуст." << endl;
	}
	system("pause");
}

void makeChoice(SOCKET sock) {
	int choice;
	char chBuf[256];
	string alt;
	int num;
	char numBuf[256], altBuf[256];
	recv(sock, numBuf, sizeof(numBuf), 0);
	num = atoi(numBuf);
	if (num != 0) {
		system("cls");
		for (int i = 0; i < num; i++) {
			recv(sock, altBuf, 200, 0);
			alt = string(altBuf);
			vecAlternatives.push_back(alt);
		}

		for (int i = 0; i < vecAlternatives.size() - 1; i++) {
			for (int j = i + 1; j < vecAlternatives.size(); j++) {
				cout << vecAlternatives[i] << " лучше, чем " << vecAlternatives[j] << " ?" << endl;
				yesOrNo();
				cin >> choice;
				itoa(choice, chBuf, 10);
				send(sock, chBuf, sizeof(chBuf), 0);
			}
		}
	}
	else {
		cout << "Список альтернатив пуст." << endl;
	}
	system("pause");
}