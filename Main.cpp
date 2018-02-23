#include <iostream>
#include <fstream>
#include "lexanalyzer.h"
#include <string.h>
using namespace std;



int main(int argc, char **argv)
{
	Scanner scan("file.txt");
	for (int i = 0; i < 10; i++){
		cout << scan.get_lex() << endl;
	}
	return 0;
}
