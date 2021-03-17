#include "std_lib_facilities.h"

constexpr char number = '8'; 
constexpr char quit = 'q';//quit
constexpr char print = ';'; // print 
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char let = '=';
const string pow_function = "pow";
const string sqrt_function = "sqrt";
const string declkey = "#";   // declaration keyword
const string quit_string = "exit";//quit keyword


double expression();

class Variable {
public:
	string name;
	double value;
};

vector<Variable> var_table; // search and store variables and their values

bool is_declared(string var)
{  
    //is var already in var_table

	for (const auto& v : var_table)
		if (v.name == var) return true;
	return false;
}

double define_name (string var, double val)
{
    // add (var,var1) to var_table

	if (is_declared(var)) 
        error(var, " declared twice");
	var_table.push_back(Variable{var,val});
	return val;
}

double get_value(string s)//return variable
{
	for(const auto& v : var_table)
		if (v.name == s) return v.value;
	error("get: undefined variable", s);
}

void set_value(string s, double d) // set the variable name s 
{
	for (auto& v : var_table)
		if(v.name == s){
			v.value = d;
			return;
		}
		error("set: undefined variable", s);
}

class Token{
public:
	char kind;
	double value;
	string name;
	Token(): kind(0) {}
	Token(char ch): kind(ch), value(0) {}
	Token(char ch, double val): kind(ch), value(val) {}
	Token(char ch, string n): kind(ch), name(n) {}
};

class Token_stream {
public:
	Token_stream();
	Token get();
	void putback(Token t);
	void ignore(char c); 
private:
	bool full;
	Token buffer;
};

Token_stream::Token_stream() :full(false), buffer(0) {}

void Token_stream::putback(Token t)
{
	if (full) 
        error("putback() into full buffer");
	buffer = t;
	full = true;
}

Token Token_stream::get()
{

	if (full)  // check if token is already there 
    {
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;

	switch (ch){
		case print:
		case quit:
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '=':
			return Token(ch); // let each character represent itself
		case '.':
		case '0': 
        case '1':
        case '2':
        case '3':
        case '4':
    	case '5': 
        case '6': 
        case '7': 
        case '8': 
        case '9':
    	{
    		cin.putback (ch); // put the number back into the stream.
    		double val;
    		cin >> val;
    		return Token(number, val);
    	}
    	default: 
    	{
    		if (isalpha(ch)){
    			string s;
    			s += ch; // s = s+ch
    			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) 
                     s+=ch;

    			cin.putback(ch);
    			if (s == declkey) 
                    return Token{let};

                if( s == quit_string)
                    return Token(quit);

                if ( s == pow_function ) 
					return sqrt();    
                
                if ( s == sqrt_function ) 
					return pow();

    			else if (is_declared(s))
    				return Token(number, get_value(s));

    			return Token{name,s};
    		}
    		error("Bad token");
            return 0;
    	}
	}
}

void Token_stream::ignore(char c){

	if (full && c == buffer.kind){
		full = false;
		return;
	}
	full = false;

	char ch = 0;
	while (cin>>ch)
		if (ch==c) return;
}

Token_stream ts;

double primary(){

	Token t = ts.get();
	switch (t.kind){
		case '(':
		{
			double d = expression();
			t = ts.get();
			if (t.kind != ')') error ("')' expected");
			return d;
		}
		case number:
			return t.value;
		case '-':
			return - primary();
		case '+':
			return primary();
		default:
			error("primary expected");
	}
}

double term(){

	double left = primary();
	Token t = ts.get();
	while(true){
		switch (t.kind){
			case '*':
				left *= primary();
				t = ts.get();
				break;
			case '/':
			{
				double d = primary();
				if (d == 0) error ("divide by zero");
				left /= d;
				t = ts.get();
				break;
			}
			case '%':
			{
				double d = primary();
				if (d == 0) error ("%: Zero oszto");
				left = fmod (left, d);
				t = ts.get();
				break;
				/*
				int i1 = narrow_cast<int>(left);
				int i2 = narrow_cast<int>(primary());
				if (i2 == 0) error ("%: Zero oszto");
				left = i1 % i2;
				t = ts.get();
				break;
				*/
			}
			default:
				ts.putback(t);
				return left;
		}
	}
}

double expression(){

	double left = term();
	Token t = ts.get();
	while (true){
		switch(t.kind){
			case '+':
				left += term();
				t = ts.get();
				break;
			case '-':
				left -= term();
				t = ts.get();
				break;
			default:
				ts.putback(t);
				return left;
		}
	}
}

void clean_up_mess(){
	ts.ignore(print);
}

double declaration(){
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);

	double d = expression();
	define_name(var_name, d);
	return d;
}

double statement(){
	Token t = ts.get();
	switch(t.kind){
		case let:
			return declaration();
		default:
			ts.putback(t);
			return expression();
	}
}

void calculate(){
	
/*	double val = 0;

	while (cin)
		try {

		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.putback(t);
		cout << "=" << statement() << endl;
		*/
	while (cin)
	try {
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.putback(t);
		cout << "=" << statement() << endl;
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}

double pow()
{
	Token t1 = ts.get();
	if (t1.kind != '(')
		error("'(' expected!");

	Token t2 = ts.get();
	double x = t2.value;

	Token t3 = ts.get();
	if (t3.kind != ',')
		error("',' expected!");

	Token t4 = ts.get();
	int i = t4.value;

	return power(x, i);
}

double sqrt ()
{
	char ch;
    cin >> ch;
	if (ch != '(')
		error("'(' expected!");
	cin.putback(ch);
	double d = expression();
	if (d < 0) 
		error("The number in sqrt root <0");
	return sqrt(d);
	}

int power (double x,int i)
{
	int n=0 , val=1;
	for ( ; n < i; n++)
		val *= x;
	return val;
   }

}

int main() 

try 
{
      cout
    << "Welcome to our simple calculator.\nPlease enter expressions using floating-point numbers.\n"
    << "You can use these operators: + - */ \n"
    << "Also,you can add an 'x' to end expression  and add an ';'to print\n ";

	define_name("pi", 3.1415926535);
	define_name("e", 2.7182818284);
    define_name("k",1000);
	calculate();

	return 0;
}

catch (exception& e)
{
	cerr << e.what() << endl;
	return 1;
}

catch (...) 
{
	cerr << "exception\n";
	return 2;
}
