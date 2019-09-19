/*
	File: HashTable.cpp
	CMSC 341 Project 5
	Author: Andrew Ingson (aings1@umbc.edu)
	Date: 12/9/2018

*/

#include "HashTable.h"

using namespace std;

// constructor
HashTable::HashTable(int usrCap) {
	// check to see if we are too big
	int cap = usrCap;
	if (cap > 199999) {
	    throw out_of_range(" requested cap is larger than 199999 ");
	} else if (cap < 101) {
	    cap = 101;
	}
	// make sure table size is prime
	cap = roundUpPrime(cap);
    cout << "Making hashtable of capacity " << cap << endl;

    // fill out primary/old array with null data
    m_old.m_data = new char*[cap];
	for (int i = 0; i < cap; i++) {
	    m_old.m_data[i] = NULL;
	}
	m_old.m_cap = cap;
	m_old.m_size = 0;
    m_old.m_loadFactor = 0.0;
	m_old.rehash = false;

	// prep max array even though we don't need it yet
    m_max.m_data = new char*[cap*16];
    for (int i = 0; i < cap; i++) {
        m_max.m_data[i] = NULL;
    }
    m_max.m_cap = cap;
    m_max.m_size = 0;
    m_max.m_loadFactor = 0.0;
    m_max.rehash = false;
}

// copy constructor
HashTable::HashTable(HashTable &other) {

}

// destructor
HashTable::~HashTable() {
	// destructor
	// free data from old array
	// TODO Set up free()

	for(int i = 0; i < m_old.m_cap; i++) {
	    if (m_old.m_data[i] != NULL) {
	        free(m_old.m_data[i]);
	    }
	}
	//delete m_old.m_data;
	//m_old.m_data = NULL;
	// free data from new array
	/*
    for(int i = 0; i < m_new.m_cap; i++) {
        if (m_new.m_data[i] != NULL) {
            free(m_new.m_data[i]);
        }
    }*/
	//delete m_new.m_data;
	//m_new.m_data = NULL;

}

// assignment operator
const HashTable &HashTable::operator=(HashTable &rhs) {
    // TODO assignment operator
    // copy all the tables over
    m_old.m_data = rhs.m_old.m_data;
    m_old.m_size = rhs.m_old.m_size;
    m_old.m_cap = rhs.m_old.m_cap;
    m_old.m_loadFactor = rhs.m_old.rehash;
    m_old.rehash = rhs.m_old.rehash;

    m_new.m_data =       rhs.m_new.m_data;
    m_new.m_size =       rhs.m_new.m_size;
    m_new.m_cap =        rhs.m_new.m_cap;
    m_new.m_loadFactor = rhs.m_new.rehash;
    m_new.rehash =       rhs.m_new.rehash;

    m_max.m_data =       rhs.m_max.m_data;
    m_max.m_size =       rhs.m_max.m_size;
    m_max.m_cap =        rhs.m_max.m_cap;
    m_max.m_loadFactor = rhs.m_max.rehash;
    m_max.rehash =       rhs.m_max.rehash;

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
    // calculate index to try to put str into
    unsigned int key = hashCode(str);
    // check if we need to start our INCREMENTAL REHASH!!!!!!
    if (m_old.m_loadFactor >= 0.5) {
        m_old.rehash = true;
    }

    if (!isRehashing()) {
        // use hash key to find initial index index
        int index = key % m_old.m_cap;
        //cout << "INDEX IS " << index << " or " << key << "%" << m_old.m_cap << endl;
        // flag to check whether we have inserted correctly
        bool success = false;
        // count to see whether we need to force rehashing due to over clustering
        int clusterCount = 0;
        bool needRehash = false;
        // loop for probing
        while (!success) {
            // check for clustering
            if (!(m_old.m_data[index] == NULL || m_old.m_data[index] == DELETED)) {
                clusterCount++;
              //  cout << "at index " << index << ", set cluster count to " << clusterCount << endl;
            }
            // check to see if the space is something we can insert into
            if (m_old.m_data[index] == NULL || m_old.m_data[index] == DELETED) {
                success = true;
                char * tempStr = strdup(str);
                m_old.m_data[index] = tempStr;
                m_old.m_size++;
                clusterCount++;
               // cout << "inserting " << str << " at " << index << ", CC is " << clusterCount<< endl;
                // check if we need to reset cluster count
                if ((m_old.m_data[index] == NULL || m_old.m_data[index] == DELETED) &&  clusterCount < 10) {
                 //   cout << "clusterCount is " << clusterCount << "\nset cluster count to 0\n";
                    clusterCount = 0;
                }
            } else {
                // check if we need to wrap the index around
                if (index >= m_old.m_cap) {
                    index = 0;
                } else {
                    index++;
                }
            }



            if (clusterCount >= 10) {
               // cout << "Breaking old loop for rehash\n";
                m_old.rehash = true;
                needRehash = true;
                success = true;
                int newCap = roundUpPrime(size()*4);
                if (newCap < tableSize()){
                    newCap = roundUpPrime(tableSize()+1);
                }
              //  cout << "Creating new table with capacity of " << newCap << endl;
                m_new.m_data = new char*[newCap];
                for (int i = 0; i < newCap; i++) {
                    m_new.m_data[i] = NULL;
                }
                m_new.m_cap = newCap;
                m_new.m_size = 0;
                m_new.m_loadFactor = 0.0;
                m_new.rehash = false;
                clusterCount--;
                while (clusterCount >= 0) {
                    unsigned int key2 = hashCode(m_old.m_data[index - (clusterCount)]);
                    bool innerSuccess = false;
                    int j = key2 % m_new.m_cap;
                    //cout << "INDEX IS " << index << " or " << key << "%" << m_old.m_cap << endl;
                    // flag to check whether we have inserted correctly
                    //bool success = false;

                    while (!innerSuccess) {
                        // check to see if the space is something we can insert into
                        if (m_new.m_data[j] == NULL || m_new.m_data[j] == DELETED) {
                            innerSuccess = true;
                            //char *tempStr = strdup(str);
                            m_new.m_data[j] = m_old.m_data[index - (clusterCount)];
                            remove(m_old.m_data[index - (clusterCount)]);
                            m_new.m_size++;
                           // cout << "inserting " << m_old.m_data[index - (clusterCount)] << " at " << j << endl;
                        } else {
                            // check if we need to wrap the index around
                            if (j >= m_new.m_cap) {
                                j = 0;
                            } else {
                                j++;
                            }
                        }
                    }
                    clusterCount--;
                    m_new.m_loadFactor = float(m_new.m_size)/m_new.m_cap;
                }
                //break;
            }
        }
        // refresh load factor so we can check if we need to rehash
        m_old.m_loadFactor = float(m_old.m_size)/m_old.m_cap;
        // check rehash conditions
        if (m_old.m_loadFactor >= 0.5) {
          // cout <<"Incremental Rehash triggered due to load factor being >=0.5\n";
           // cout << "Load factor is " << m_old.m_loadFactor << endl;
            m_old.rehash = true;
            needRehash = true;
        }
        if (clusterCount >= 10) {
           // cout << "Incremental Rehash triggered due to a cluster being >=10\n";
            m_old.rehash = true;
            needRehash = true;
        }
        // create new table if we need to rehash
        /*
        if (needRehash) {
            // var to hold new capacity
            int newCap = tableSize(0)*2;
            cout << "Creating new table with capacity of " << newCap << endl;
            m_new.m_data = new char*[newCap];
            for (int i = 0; i < newCap; i++) {
                m_new.m_data[i] = NULL;
            }
            m_new.m_cap = newCap;
            m_new.m_size = 0;
            m_new.m_loadFactor = 0.0;
            m_new.rehash = false;
            success = false;
            // put overflowed value into new table
            while (!success) {
                // check to see if the space is something we can insert into
                if (m_new.m_data[index] == NULL || m_new.m_data[index] == DELETED) {
                    success = true;
                    char *tempStr = strdup(str);
                    m_new.m_data[index] = tempStr;
                    m_new.m_size++;
                    cout << "inserting " << str << " at " << index << endl;
                } else {
                    // check if we need to wrap the index around
                    if (index >= m_new.m_cap) {
                        index = 0;
                    } else {
                        index++;
                    }
                }
            }
            m_new.m_loadFactor = float(m_new.m_size)/m_new.m_cap;
        }*/
        // adjust load factor
        m_old.m_loadFactor = float(m_old.m_size)/m_old.m_cap;
    } else {
        // TODO setup basic rehashing
       // cout << "I R is in effect \n";
        int index = key % m_new.m_cap;
        //cout << "INDEX IS " << index << " or " << key << "%" << m_old.m_cap << endl;
        // flag to check whether we have inserted correctly
        bool success = false;

        while (!success) {
            // check to see if the space is something we can insert into
            if (m_new.m_data[index] == NULL || m_new.m_data[index] == DELETED) {
                success = true;
                char *tempStr = strdup(str);
                m_new.m_data[index] = tempStr;
                m_new.m_size++;
                cout << "inserting " << str << " at " << index << endl;
            } else {
                // check if we need to wrap the index around
                if (index >= m_new.m_cap) {
                    index = 0;
                } else {
                    index++;
                }
            }
        }
        m_new.m_loadFactor = float(m_new.m_size)/m_new.m_cap;


    }
    // TODO Wrap up incremental rehash if under load factor is under 0.03
}

void HashTable::dump() {
    // old table
    cout << "HashTable #1: size = " << size() << ", tableSize = " << tableSize()<<", LF is "
        << m_old.m_loadFactor << endl;
    for (int i = 0; i < m_old.m_cap; i++) {
        cout << "H1[" << i << "] = ";
        if (m_old.m_data[i] != NULL) {
            if (m_old.m_data[i] == DELETED) {
                cout << "DELETED";
            } else {
                cout << m_old.m_data[i];
            }
        }
        cout << endl;
    }
    // if a rehash is underway, dump the second table too
    if (isRehashing()) {
        cout << "\n\nHashTable #2: size = " << size(1) << ", tableSize = " << tableSize(1)<<", LF is "
             << m_new.m_loadFactor << endl;
        for (int i = 0; i < m_new.m_cap; i++) {
            cout << "H2[" << i << "] = ";
            if (m_new.m_data[i] != NULL) {
                if (m_new.m_data[i] == DELETED) {
                    cout << "DELETED";
                } else {
                    cout << m_new.m_data[i];
                }
            }
            cout << endl;
        }
    }


}

char * HashTable::remove(const char *str) {
    char * tempStr = strdup(str);
    // hash key so we know where to jump to
    unsigned int key = hashCode(str);
    // check if we are rehashing and act accordingly
    if(!isRehashing()) {
        // calculate index and make count variable so we know fi we haven't found anything
        int i = key % m_old.m_cap;
        int count = 0;
        while (count < tableSize()) {
            if (m_old.m_data[i] != NULL) {
                if (0 == strcmp(m_old.m_data[i], tempStr)) {
                    m_old.m_data[i] = DELETED;
                    m_old.m_size--;
                    m_old.m_loadFactor = float(m_old.m_size) / m_old.m_cap;
                    return tempStr;
                }
            }
            // increment both counters
            count++;
            i++;
            // check to see if we need to loop
            if (i >= tableSize()) {
                i = 0;
            }

        }
        return NULL;

    } else {

    }
    return NULL;
    // TODO Wrap up rehashing if load factor is under 0.03
}

bool HashTable::find(const char *str) {
    bool result = false;
    // TODO finish rehashing when load is 0.03 or smaller

    // create temp string to compare against
    char * tempStr = strdup(str);
    unsigned int key = hashCode(str);
    // check if we need to start INCREMENTAL REHASHING!!!!!
    if (m_old.m_loadFactor >= 0.5) {
        m_old.rehash = true;
    }
    // check which table we should look in
    if(!isRehashing()) {
        int count = 0;
        int i = key % m_old.m_cap;
        // TODO If we find it beyond ten spaces, start a rehash
        while (count < tableSize()) {
           // cout << m_old.m_data[i] << " at " << i << endl;
           if (m_old.m_data[i] != NULL) {
               if (0 == strcmp(m_old.m_data[i], tempStr)) {
                  // cout << "Found " << tempStr << endl;
                   result = true;
               }
           }
           // increment both counters
           count++;
           i++;
           // check to see if we need to wrap around
           if (i >= tableSize()) {
               i = 0;
           }
           if (count >= 10) {
             //  cout << "I R triggered by find of 10 or more\n";
               m_old.rehash = true;
            //   break;
               //count = tableSize();
           }
        }
        if(isRehashing()) {
            // initialization for new heap
          //  cout << "FIND: Breaking old loop for rehash\n";
            m_old.rehash = true;
            //needRehash = true;
            //success = true;
            int newCap = roundUpPrime(size()*4);
            if (newCap < tableSize()){
                newCap = roundUpPrime(tableSize()+1);
            }
           // cout << "Creating new table with capacity of " << newCap << endl;
            m_new.m_data = new char*[newCap];
            int tempIndex = i-1;
            for (int i = 0; i < newCap; i++) {
                m_new.m_data[i] = NULL;
            }
            m_new.m_cap = newCap;
            m_new.m_size = 0;
            m_new.m_loadFactor = 0.0;
            m_new.rehash = false;
            //count--;
            while (count >= 0) {
                unsigned int key2 = hashCode(m_old.m_data[tempIndex-count]);
                bool innerSuccess = false;
                int j = key2 % m_new.m_cap;
                //cout << "INDEX IS " << index << " or " << key << "%" << m_old.m_cap << endl;
                // flag to check whether we have inserted correctly
                //bool success = false;

                while (!innerSuccess) {
                    // check to see if the space is something we can insert into
                    if (m_new.m_data[j] == NULL || m_new.m_data[j] == DELETED) {
                        innerSuccess = true;
                        //char *tempStr = strdup(str);
                        m_new.m_data[j] = m_old.m_data[i - (count)];
                        remove(m_old.m_data[i - (count)]);
                        m_new.m_size++;
                       // cout << "FIND: moving " << m_old.m_data[i - (count)] << " at " << j << endl;
                    } else {
                        // check if we need to wrap the index around
                        if (j >= m_new.m_cap) {
                            j = 0;
                        } else {
                            j++;
                        }
                    }
                }
                count--;
                m_new.m_loadFactor = float(m_new.m_size) / m_new.m_cap;
            }
        }


    } else {
        // TODO incremental rehashing for find
        // Since INCREMENTAL REHASHING is at play, we might have to search both
        //


        // search new table
        int count = 0;
        int i = key % m_old.m_cap;
        // TODO If we find it beyond ten spaces, start a rehash
        while (count < tableSize()) {
            // cout << m_old.m_data[i] << " at " << i << endl;
            if (m_old.m_data[i] != NULL) {
                if (0 == strcmp(m_old.m_data[i], tempStr)) {
                    // cout << "Found " << tempStr << endl;
                    result = true;
                }
            }
            // increment both counters
            count++;
            i++;
            // check to see if we need to wrap around
            if (i >= tableSize()) {
                i = 0;
            }
            if (count >= 10) {
               // cout << "FIND: I R triggered by find of 10 or more\n";
                count = tableSize();
                m_old.rehash = true;
            }
        }

        int cReverse = 0;
        int cForward = 0;
        while (m_old.m_data[i-cReverse] != NULL && m_old.m_data[i-cReverse] != DELETED) {
            cReverse++;
        }
      //  cout << "cReverse is " << cReverse << endl;
        while (m_old.m_data[i+cForward] != NULL && m_old.m_data[i+cForward] != DELETED) {
            cForward++;
        }
      //  cout << "cForward is " << cForward << endl;
        int clusterRange = cReverse + cForward + 1;

        int index = key % m_old.m_cap;
        // index = index - cReverse;
        i = key % m_old.m_cap;
       // i = i - cReverse;
        //cout << "INDEX IS " << index << " or " << key << "%" << m_old.m_cap << endl;
        // flag to check whether we have inserted correctly
        bool success = false;
        //cout << "Cluster Range is " << clusterRange << endl;
        for (int counter = 0; counter < clusterRange; counter++) {
            key = hashCode(m_old.m_data[i+counter]);
            index = key % m_new.m_cap;
            success = false;
            while (!success) {
                // check to see if the space is something we can insert into
                if (m_new.m_data[index] == NULL || m_new.m_data[index] == DELETED) {
                    success = true;
                    //char *tempStr = strdup(str);
                    m_new.m_data[index] = m_old.m_data[i+counter];
                    m_new.m_size++;
                    //cout << "FIND: inserting " << m_old.m_data[i+counter] << " at " << index+counter << endl;
                } else {
                    // check if we need to wrap the index around
                    if (index >= m_new.m_cap) {
                        index = 0;
                    } else {
                        index++;
                    }
                }
            }

            m_new.m_loadFactor = float(m_new.m_size) / m_new.m_cap;
        }
    }
    return result;

}

bool HashTable::isRehashing() {
    m_old.m_loadFactor = float(m_old.m_size)/m_old.m_cap;
    return m_old.rehash;
}

int HashTable::size(int table) {
    // check which table we want to look at
    if (table == 0) {
        return m_old.m_size;
    } else if (table == 1) {
        return m_new.m_size;
    } else {
        return -1;
    }
}

int HashTable::tableSize(int table) {
    if (table == 0) {
        return m_old.m_cap;
    } else if (table == 1) {
        return m_new.m_cap;
    } else {
        return -1;
    }
}

const char *HashTable::at(int index, int table) {
    if (table == 0) {
        return m_old.m_data[index];
    } else {
        return m_new.m_data[index];
    }
}

char * const HashTable::DELETED  = (char *) &DELETED;
