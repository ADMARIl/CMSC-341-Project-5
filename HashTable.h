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
#include <cstring>
#include "primes.h"
//#include "words.h"

using namespace std;

struct SubTable {
    char ** m_data = NULL;
    int m_size = 0;
    int m_cap = 0;
    float m_loadFactor = 0.0;
    bool rehash = false;
};

class HashTable {
public:
    // boring constructor stuff
	HashTable(int cap = 101);
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

    static char * const DELETED ;

	private:
        //int m_size;
       // int m_cap;
		SubTable m_old; // table that might need to rehash
        SubTable m_new; // table that we move things to
        SubTable m_max;
		//char ** m_new;
};

#endif
