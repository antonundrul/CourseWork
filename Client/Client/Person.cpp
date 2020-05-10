#include "Person.h"

Person::Person() {
	this->idPerson = 0;
	this->name = "";
	this->surname = "";
	this->age = 0;
}

Person::Person(int id, string name, string surname, int age) {
	this->idPerson = id;
	this->name = name;
	this->surname = surname;
	this->age = age;
}

void Person::setName(string name) {
	this->name = name;
}

string Person::getName() {
	return this->name;
}

void Person::setSurname(string surname) {
	this->surname = surname;
}

string Person::getSurname() {
	return this->surname;
}

void Person::setAge(int age) {
	this->age = age;
}

int Person::getAge() {
	return this->age;
}

