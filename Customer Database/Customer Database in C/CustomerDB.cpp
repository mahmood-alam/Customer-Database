/*
 * Name:
 * EID:
 * Project 7, CRM part 2
 * EE 312, Spring 2017
 */
#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(String name) { // done, please do not edit
	this->bottles = 0;
	this->rattles = 0;
	this->diapers = 0;
	this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

int CustomerDB::size(void) {
	return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
	delete[] this->data;
}

void CustomerDB::clear(void) { // done, please do not edit
	delete[] this->data;
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
	assert(k >= 0 && k < this->length);
	return this->data[k];
}

Customer& CustomerDB::operator[](String name) { // not done, your effort goes here
	if (isMember(name)){
		for(int i=0; i<this->length; i++){
			if(this->data[i].name == name){
				return this->data[i];
			}
		}
		return *this->data;
	}else{
		this->length++;
		Customer c = Customer(name);
		if (this->capacity==this->length) {
			this->capacity *= 2;
			Customer *newdata = new Customer[this->capacity];
			for (int i = 0; i < this->length; i++) {
				newdata[i] = data[i];
			}
			delete[] data;
			this->data = newdata;
		}
		this->data[this->length-1].name = c.name;
		this->data[this->length-1].bottles = c.bottles;
		this->data[this->length-1].diapers = c.diapers;
		this->data[this->length-1].rattles = c.rattles;

		return this->data[this->length-1];
	}

}



bool CustomerDB::isMember(String name) {
	int i = 0;
	while (i < length){
		// data[i].name == name;
		if (this->data[i].name == name){
			return true;
		}
		i++;
	}
	//this->length++;
	return false;
	// not done, your effort goes here
}

