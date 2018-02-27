#include <iostream>
#include <fstream>
#include "lexical.h"
using namespace std;

Table_ident TID;

int main(int argc, char **argv)
{
    Scanner scan("file.txt");
    try{
        while(1){
            cout << scan.get_lex(TID) << endl;
        }
    }catch (char c){
        cout << c << endl;
    }

    return 0;
}
