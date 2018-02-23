#include <iostream>
#include <fstream>
#include "lexanalyzer.h"
#include <string.h>
using namespace std;

Table_ident TID(100);

int main(int argc, char **argv)
{
	Scanner scan("file.txt");
	for (int i = 0; i < 10; i++)
		scan.get_lex();
	for (int i = 0; i < 10; i++)
		cout << TID[i] << endl;
	return 0;
}
