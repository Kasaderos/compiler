#pragma once
using namespace std;

enum type_of_lex {
	LEX_NULL,
	LEX_AND,
	LEX_BEGIN,
	LEX_WRITE,
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
	LEX_FIN,
	LEX_SEMICOLON,
	LEX_COMMA,
	LEX_GEQ,
	LEX_NUM,
	LEX_ID,
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
	POLIZ_LABEL,
	POLIZ_ADDRESS,
	POLIZ_GO,
	POLIZ_FGO
};

class Lex
{
	type_of_lex t_lex;
	int	    v_lex;
public:
	Lex(type_of_lex t = LEX_NULL, int v = 0){
        t_lex = t; 
        v_lex = v;
    }
	type_of_lex get_type();
	int get_value();
	friend ostream & operator << (ostream & s, Lex l);
};

class Scanner
{
	enum				 state { H, IDENT, NUMB, COM, ALE, DELIM, NEQ };
	static char			 *TW[];
	static type_of_lex words[];
	static char			 *TD[];
	static type_of_lex  dlms[];
	state					CS;
	ifstream			  file; // изменено FILE *fp;
	char					 c;
	char			   buf[80];
	int				   buf_top;
	void clear();
	void add();
	int look(const char *buf, char **list);
	void getchar(); // изменено void gc();
public:
	Scanner(const char *filename);
	Lex get_lex();
};



class Ident
{
	char *			name;
	bool		 declare;
	type_of_lex		type;
	bool		  assign;
	int			   value;
public:
	Ident();
	char * get_name();
	void put_name(const char * n);
	bool get_declare();
	void put_declare();
	type_of_lex get_type();
	void put_type(type_of_lex t);
	bool get_assign();
	void put_assign();
	int get_value();
	void put_value(int v);
};

class Table_ident
{
	Ident	 * p;
	int		size;
	int		 top;
public:
	Table_ident(int max_size);
	~Table_ident();
	Ident & operator[] (int k);
	int put(const char * buf);
};
