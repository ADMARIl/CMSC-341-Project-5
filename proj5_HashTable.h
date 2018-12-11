/*
	File: HashTable.h
	CMSC 341 Project 5
	Author: Andrew Ingson (aings1@umbc.edu)
	Date: 12/9/2018

*/
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <stdexcept>
#include "primes.h"
#include "words.h"

using namespace std;

class HashTable {
	public:
        // boring constructor stuff
		HashTable(int size=101);
        HashTable (HashTable& other) ;
		~HashTable();
        const HashTable& operator= (HashTable& rhs) ;
        // table operators
        void insert(const char *str);
        bool find(const char *str);
        char * remove(const char *str);
        // provided hash function
		unsigned int hashCode(const char *str);
		// grading functions
		bool isRehashing() ;
        int tableSize(int table=0) ;
        int size(int table=0) ;
        const char * at(int index, int table=0) ;
        // print stats and contents
        void dump();

	private:
        int m_size;
		char *m_data;
		float m_load;

};

#endif
