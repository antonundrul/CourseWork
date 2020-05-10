#pragma once

#include <iostream>
#include <string>

using namespace std;

class Person {
protected:
	int idPerson;
	string name;
	string surname;
	int age;
public:
	Person();
	Person(int, string, string, int);
	void setId(int id);
	int getId();
	void setName(string name);
	string getName();
	void setSurname(string surname);
	string getSurname();
	void setAge(int age);
	int getAge();

};