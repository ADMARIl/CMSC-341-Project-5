/*
	File: Driver.cpp
	CMSC 341 Project 5
	Author: Andrew Ingson (aings1@umbc.edu)
	Date: 12/9/2018

*/

#include <iostream>
#include "HashTable.h"
#include "words.h"

using namespace std;

int main() {
    // create hash table of size 107
    HashTable T(107);

    T.insert("I");
    T.insert("really");
    T.insert("hope");
    T.insert("you");
    T.insert("enjoy");
    T.insert("this");
    T.insert("CMSC");
    T.insert("Three");
    T.insert("Forty");
    T.insert("One");
    T.insert("project");

    cout << "----------------------------------------------------\n" ;
    cout << "Original hash table\n" ;
    cout << "----------------------------------------------------\n" ;
    T.dump() ;
    cout << "----------------------------------------------------\n" ;

    // insert things
    T.insert("undulation") ;     //  9
    T.insert("impertinent") ;    // 10
    T.insert("maladies") ;       // 10 -> 11
    T.insert("dominions") ;	// 12

    cout << "----------------------------------------------------\n" ;
    cout << "Hash table insertions.\n" ;
    cout << "----------------------------------------------------\n" ;
    T.dump() ;
    cout << "----------------------------------------------------\n" ;

    //insert things that will cause it to rehash
    T.insert("tributes") ;	// 21
    T.insert("skulduggery") ;	// 22
    T.insert("convulse") ;	// 23
    T.insert("frothed") ;	// 24
    T.insert("horrify") ;	// 25
    T.insert("blackmailers") ;	// 26
    T.insert("defenestrated") ;	// 27
    T.insert("garrison") ;	// 23 -> 28
    T.insert("lidless") ;	// 22 -> 29
    T.insert("eye") ;            // 21 -> 30, should trigger inc. rehash

    cout << "----------------------------------------------------\n" ;
    cout << "Hash table insertions + rehash.\n" ;
    cout << "----------------------------------------------------\n" ;
    T.dump() ;
    cout << "----------------------------------------------------\n" ;

    // test if we can find things
    const char *str ;
    bool found ;

    if( T.find(str="skulduggery") ) {
        cout << "Found " << str << endl ;
    } else {
        cout << "Did not find " << str << endl ;
    }

    // test for removing things
    T.remove("really");
    T.remove("CMSC");

    cout << "\n\n" ;
    cout << "----------------------------------------------------\n" ;
    cout << "Hash table after removes\n" ;
    cout << "----------------------------------------------------\n" ;
    T.dump() ;
    cout << "----------------------------------------------------\n" ;
    cout << "Driver Finished\n";

    /*
                 ▄              ▄
                ▌▒█           ▄▀▒▌
                ▌▒▒█        ▄▀▒▒▒▐
               ▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐
             ▄▄▀▒░▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐
           ▄▀▒▒▒░░░▒▒▒░░░▒▒▒▀██▀▒▌
          ▐▒▒▒▄▄▒▒▒▒░░░▒▒▒▒▒▒▒▀▄▒▒▌
          ▌░░▌█▀▒▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐
         ▐░░░▒▒▒▒▒▒▒▒▌██▀▒▒░░░▒▒▒▀▄▌
         ▌░▒▄██▄▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▌
        ▌▒▀▐▄█▄█▌▄░▀▒▒░░░░░░░░░░▒▒▒▐
        ▐▒▒▐▀▐▀▒░▄▄▒▄▒▒▒▒▒▒░▒░▒░▒▒▒▒▌
        ▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒▒▒░▒░▒░▒▒▐
         ▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒░▒░▒░▒░▒▒▒▌
         ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▒▄▒▒▐
          ▀▄▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▄▒▒▒▒▌
            ▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀
              ▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀
                 ▒▒▒▒▒▒▒▒▒▒▀▀



 _____ _                 _           __
|_   _| |               | |         / _|
  | | | |__   __ _ _ __ | | _____  | |_ ___  _ __    __ _
  | | | '_ \ / _` | '_ \| |/ / __| |  _/ _ \| '__|  / _` |
  | | | | | | (_| | | | |   <\__ \ | || (_) | |    | (_| |
  \_/ |_| |_|\__,_|_| |_|_|\_\___/ |_| \___/|_|     \__,_|
                      _
                     | |
  __ _ _ __ ___  __ _| |_
 / _` | '__/ _ \/ _` | __|
| (_| | | |  __/ (_| | |_
 \__, |_|  \___|\__,_|\__|
  __/ |
 |___/
                              _            _
                             | |          | |
 ___  ___ _ __ ___   ___  ___| |_ ___ _ __| |
/ __|/ _ \ '_ ` _ \ / _ \/ __| __/ _ \ '__| |
\__ \  __/ | | | | |  __/\__ \ ||  __/ |  |_|
|___/\___|_| |_| |_|\___||___/\__\___|_|  (_)




 */

    return 0;
}