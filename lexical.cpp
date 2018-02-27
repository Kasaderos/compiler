#include <string>
#include <cstdlib>
#include <cmath>
#include "lexical.h"
using namespace std;

const string Scanner::TWD[] = { "", "=", "i", "f", "p", "+", "-", "\n", "$"};

Lex::Lex(){
    t_lex = LEX_NULL;
    v_lex = "_";
}
Lex::Lex(type_lex t, string v){
    t_lex = t;
    v_lex = v;
}

ostream & operator << (ostream & s, Lex lx){
    s << '(' << Scanner::TWD[lx.t_lex] << ',' << lx.v_lex << ')';
    return s;    
}
Ident::Ident()
{
    declare = false;
    assign = false;
}

type_lex Scanner::types[] ={
    LEX_NULL, // 0   
    LEX_ASSIGN, // 1
    LEX_INT, // 2
    LEX_FLOAT, LEX_PRINT, LEX_FNUM, LEX_INUM, // 3, 4, 
    LEX_PLUS, LEX_MINUS, LEX_NLINE, // 5, 6, 7
    LEX_FIN, // 8
    LEX_ID, // 9
    POLIZ_ADDRESS, // 10
};

Scanner::Scanner(const char *filename)
{
    fp.open(filename);
    ST = H;
}

Scanner::~Scanner()
{
    fp.close();
}

void Scanner::gc(){
    fp >> c;
}

int Scanner::look(){
    for(int i = 0; i < NUM_WORDS; i++)
        if (!buf.compare(TWD[i]))
            return i;
    return 0;
}

Lex Scanner::get_lex(Table_ident & TID)
{
    int d, j, i, f;
    d = j = i = f;
    float flt;
    gc();   
    while (1) {
        switch (ST){
        case H:
            if (c == ' ' || c == '\t' || c == '\r')
                gc();
            else if (isalpha(c)){
                buf.clear();
                buf.push_back(c);
                gc();
                ST = IDENT;
            }else if (isdigit(c)){
                buf.clear();
                buf.push_back(c);
                ST = NUM;
                gc();    
            }else if (c == '$')
                return Lex(LEX_FIN, "");
            else
                ST = OTHER;
            break;
        case IDENT:
            if ((j = look()) > 0) {
                return Lex(types[j], to_string(j));
            }else if (isalpha(c) || isdigit(c)){
                buf.push_back(c);
                gc();
            }else {
                TID.var.insert( pair<string,string>(buf, "_"));
                return Lex(LEX_ID, "_");
            }
            break;
        case NUM:
            if (isdigit(c)){
                buf.push_back(c);
                gc();
            }else if (c == '.'){
                f = 1; 
                d = atoi(buf.c_str()); // int(string)
                buf.clear();
                gc();
            }else if (f){ 
                flt = d + atoi(buf.c_str()) / pow(10, buf.size()); // целая + дробная часть 
                return Lex(LEX_FNUM, to_string(flt));
            }else {
                return Lex(LEX_INUM, buf);
            }
            break;
        case OTHER:
            buf.clear();
            buf.push_back(c);
            if ((j = look()) > 0){
                gc();
                return Lex(types[j], to_string(j));
            }else
                throw c;
            break;
        }
    }
}
