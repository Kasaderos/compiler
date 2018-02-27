#ifndef __LEXICAL_H__
#define __LEXICAL_H__
#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

const int NUM_WORDS = 9;

enum type_lex{
    LEX_NULL, // 0   
    LEX_ASSIGN, // 1
    LEX_INT, // 2
    LEX_FLOAT, LEX_PRINT, LEX_FNUM, LEX_INUM, // 3, 4, 
    LEX_PLUS, LEX_MINUS, LEX_NLINE, // 5, 6, 7
    LEX_FIN, // 8
    LEX_ID, // 9
    POLIZ_ADDRESS, // 10
};

class Lex{
public:
    type_lex t_lex;
    string v_lex;
    Lex();
    Lex(type_lex t, string v);
    friend ostream & operator << (ostream & s, Lex lx);
};

ostream & operator << (ostream & s, Lex & lx);

class Ident{
public:
    string name;
    string val;
    bool declare;
    bool assign;
    Ident();
};

class Table_ident{
public:
	map< string, string > var;
};

class Scanner
{
    enum state {H, IDENT, NUM, OTHER};
    state ST;
    ifstream fp;
    string buf;
    char c; 
public:
    static type_lex types[];
    static const string TWD[];
    void gc();
    int look();
    Scanner(const char * filename);
    Lex get_lex(Table_ident & TID);
    ~Scanner();
};

#endif
