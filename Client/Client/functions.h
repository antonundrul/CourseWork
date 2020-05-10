#pragma once
#include <iostream>
#include <string>

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

void adminFunctions(SOCKET sock);
void userFunctions(SOCKET sock); 

void userManageFunctions(SOCKET sock);
void departmentManageFunctions(SOCKET sock);
void solveProblemFunctions(SOCKET sock);
void addAlternatives(SOCKET sock);
void viewAlternatives(SOCKET sock);
void makeChoice(SOCKET sock);