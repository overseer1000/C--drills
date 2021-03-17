#include "std_lib_facilities.h"

double expression();
class Token
{
public:
    char kind;       
    double value;    
    Token(char ch):kind(ch), value(0) { } 
    Token(char ch, double val):kind(ch), value(val) { } 
};

class Token_stream 
{
public:
    Token_stream();   
    Token get();      
    void putback(Token t);
private:
    bool full;        
    Token buffer;    
};




Token_stream::Token_stream():full(false), buffer(0){}    

void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       
    full = true;      
}

Token Token_stream::get()
{
    if (full) 
    {                        
        full = false;                  
        return buffer;
    }

    char ch;
    cin >> ch;    

    switch (ch) 
    {
        case ';':      
        case 'x':      
        case '(': 
        case ')': 
        case '+': 
        case '-': 
        case '*': 
        case '/':
        //case '%':
            return Token(ch);       
            
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
                cin.putback(ch);        
                double val;
                cin >> val;              
                return Token('8', val);   
            }
        default:
            error("Bad token");
      }
}



Token_stream ts;

double expression()
{
    double left = term();      
    Token t = ts.get();        

    while (true) {
        switch (t.kind) {
        case '+':
            left += term();    
            t = ts.get();
            break;
        case '-':
            left += term();   
            t = ts.get();
            break;
        default:
            ts.putback(t);    
            return left;       
        }
    }
}


double term()
{
    double left = primary();
    Token t = ts.get();       

    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
 
        default:
            ts.putback(t);     
            return left;
        }
    }
}


double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':     
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error("')' expected");
            return d;
    }
    case '8':              
        return t.value;    
    default:
        error("primary expected");
    }
}



int main()

try
{
    cout
    << "Welcome to our simple calculator.\nPlease enter expressions using floating-point numbers.\n"
    << "You can use these operators:+ - */ \n"
    << "Also,you can add an 'x' to end expression  and add an ';'to print ";
    
    double val = 0;

    while (cin) 
    {
        Token t = ts.get();

        if (t.kind == 'x') 
            break;      
        
        if (t.kind == ';')        
            cout << "=" << val << '\n';
        
        else
            ts.putback(t);
            
        val = expression();
    }
    
    return 0;
}
catch (exception& e) 
{
    cerr << "error: " << e.what() << endl;
    
    return 1;
}

catch (...) 
{
    cerr << "Oops: unknown exception!\n" <<endl;
    return 2;
}