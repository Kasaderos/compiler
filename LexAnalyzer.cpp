#include <iostream>
#include <fstream>
#include "lexanalyzer.h"
#include <string.h>
using namespace std;

Table_ident TID(100);

char * Scanner::TW[] =
{
	"",
	"and",
	"begin",
	"bool",
	"do",
	"else",
	"end",
	"if",
	"false",
	"int",
	"not",
	"or",
	"program",
	"read",
	"then",
	"true",
	"var",
	"while",
	"write",
	NULL
};

char * Scanner::TD[] =
{
	"",
	"@",
	";",
	",",
	":",
	":=",
	"(",
	")",
	"=",
	"<",
	">",
	"+",
	"-",
	"*",
	"/",
	"<=",
	"!=",
	">=",
	NULL
};

type_of_lex Scanner::words[] =
{
	LEX_NULL,
	LEX_AND,
	LEX_BEGIN,
	LEX_BOOL,
	LEX_DO,
	LEX_ELSE,
	LEX_END,
	LEX_IF,
	LEX_FALSE,
	LEX_INT,
	LEX_NOT,
	LEX_OR,
	LEX_PROGRAM,
	LEX_READ,
	LEX_THEN,
	LEX_TRUE,
	LEX_VAR,
	LEX_WHILE,
	LEX_WRITE,
	LEX_NULL
};

type_of_lex Scanner::dlms[] =
{
	LEX_NULL,
	LEX_FIN,
	LEX_SEMICOLON,
	LEX_COMMA,
	LEX_COLON,
	LEX_ASSIGN,
	LEX_LPAREN,
	LEX_RPAREN,
	LEX_EQ,
	LEX_LSS,
	LEX_GTR,
	LEX_PLUS,
	LEX_MINUS,
	LEX_TIMES,
	LEX_SLASH,
	LEX_LEQ,
	LEX_NEQ,
	LEX_GEQ,
	LEX_NULL
};

void Scanner::clear() {
	buf_top = 0;
	for (int j = 0; j < 80; ++j)
		buf[j] = '\0';
}

void Scanner::add() {
	buf[buf_top++] = c;
}

int Scanner::look(const char *buf, char **list) {
	int i = 0;
	while (list[i]) {
		if (!strcmp(buf, list[i]))
			return i;
		++i;
	}
	return 0;
}

void Scanner::getchar() {
	file >> c;
}

Scanner::Scanner(const char * filename){
	file.open(filename);
	CS = H;
	clear();
	getchar();
}

ostream & operator << (ostream & s, Lex l) {
	s << '(' << l.t_lex << ',' << l.v_lex << ')';
	return s;
}

/*Lex::Lex(type_of_lex t = LEX_NULL, int v = 0) { 
    t_lex = t; 
    v_lex = v;
}*/

type_of_lex Lex::get_type() { return t_lex; }

int Lex::get_value() { return v_lex; }

Ident::Ident() : declare(false), assign(false) {}

char * Ident::get_name() { return name; }

bool Ident::get_declare() { return declare; }

void Ident::put_declare() { declare = true; }

type_of_lex Ident::get_type() { return type; }

void Ident::put_type(type_of_lex t) { type = t; }

bool Ident::get_assign() { return assign; }

void Ident::put_assign() { assign = true; }

int Ident::get_value() { return value; }

void Ident::put_value(int v) { value = v; }

void Ident::put_name(const char * n) {
	name = new char[strlen(n) + 1];
	strcpy(name, n);
}

Ident & Table_ident:: operator[] (int k) { return p[k]; }

int Table_ident::put(const char * buf) {
	for (int j = 1; j < top; ++j)
		if (!strcmp(buf, p[j].get_name()))
			return j;
	p[top].put_name(buf);
	++top;
	return top - 1;
}

Table_ident::Table_ident(int max_size) {
	p = new Ident[size = max_size];
	top = 1;
}

Table_ident::~Table_ident() {
	delete[]p;
}



Lex Scanner::get_lex() {
	int d, j;
	CS = H;
	do {
		switch (CS) {
		case H:
			if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
				getchar();
			else if (isalpha(c)) {
				clear();
				add();
				getchar();
				CS = IDENT;
			}
			else if (isdigit(c)) {
				d = c - '0';
				getchar();
				CS = NUMB;
			}
			else if (c == '{') {
				getchar();
				CS = COM;
			}
			else if (c == ':' || c == '<' || c == '>') {
				clear();
				add();
				getchar();
				CS = ALE;
			}
			else if (c == '@')
				return Lex(LEX_FIN);
			else if (c == '!') {
				clear();
				add();
				getchar();
				CS = NEQ;
			}
			else
				CS = DELIM;
			break;
		case IDENT:
			if (isalpha(c) || isdigit(c)) {
				add();
				getchar();
			}
			else
				if (j = look(buf, TW))
					return Lex(words[j], j);
				else {
					j = TID.put(buf);
					return Lex(LEX_ID, j);
				}
			break;
		case NUMB:
			if (isdigit(c)) {
				d = d * 10 + (c - '0');
				getchar();
			}
			else
				return Lex(LEX_NUM, d);
			break;
		case COM:
			if (c == '}') {
				getchar();
				CS = H;
			}
			else if (c == '@' || c == '{')
				throw c;
			else
				getchar();
			break;
		case ALE:
			if (c == '=') {
				add();
				getchar();
				j = look(buf, TD);
				return Lex(dlms[j], j);
			}
			else {
				j = look(buf, TD);
				return Lex(dlms[j], j);
			}
			break;
		case NEQ:
			if (c == '=') {
				add();
				getchar();
				j = look(buf, TD);
				return Lex(LEX_NEQ, j);
			}
			else
				throw '!';
			break;
		case DELIM:
			clear();
			add();
			if (j = look(buf, TD)) {
				getchar();
				return Lex(dlms[j], j);
			}
			else
				throw c;
			break;
		}
	} while (true);
}
