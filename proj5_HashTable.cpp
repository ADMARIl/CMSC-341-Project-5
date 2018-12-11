/*
	File: HashTable.cpp
	CMSC 341 Project 5
	Author: Andrew Ingson (aings1@umbc.edu)
	Date: 12/9/2018

*/

#include "HashTable.h"
using namespace std;
// constructor
HashTable::HashTable(int size) {
	// check to see if we are too big
	if (size > 199999) {
	    throw std::out_of_range(" requested size is larger than 199999 ");
	} else if (size < 101) {
	    size = 101;
	}
	// make sure table size is prime
	size = roundUpPrime(size);

	m_size = size;
	m_data = new char [size];
	m_load = 0.0;
}

// copy constructor
HashTable::HashTable(HashTable &other) {

}

// destructor
HashTable::~HashTable() {
	// destructor
	delete m_data;
	m_data = NULL;
}

// assignment operator
const HashTable &HashTable::operator=(HashTable &rhs) {
    return *this;
}

// provided hash function
unsigned int HashTable::hashCode(const char *str) {
   unsigned int val = 0 ;
   const unsigned int thirtyThree = 33 ;  // magic number from textbook

   int i = 0 ;
   while (str[i] != '\0') {
      val = val * thirtyThree + str[i] ;
      i++ ;
   }
   return val ;
}

void HashTable::insert(const char *str) {

}

void HashTable::dump() {
    // TODO: Make correct syntax
}

char * HashTable::remove(const char *str) {

}

bool HashTable::find(const char *str) {
    return false;
}

bool HashTable::isRehashing() {
    return false;
}

int HashTable::tableSize(int table) {
    return 0;
}

int HashTable::size(int table) {
    return 0;
}

const char *HashTable::at(int index, int table) {
    return nullptr;
}





