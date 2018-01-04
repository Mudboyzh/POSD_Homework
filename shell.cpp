#include "parser.h"
#include "scanner.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char **argv) {
    string input, part, code = "";
    stringstream inputStream;
    Parser *parser;
    while (true) {
        while ( input == "" || input.back() != '.') {
            if (input == "" )
                cout << "?- ";
            else 
                cout << "|  ";
            getline(cin, input);
            inputStream << input;
            while ( inputStream >> part) 
                code += part ;
            
            inputStream.str("");  // must have 
            inputStream.clear();  // for reuse inputStream
        }
        
        if ( code == "halt.") 
            break; 
        else {
            parser = new Parser(Scanner(code));
            try {
                parser->buildExpression();
                cout << parser->result() << endl;
            }
            catch( string &errorMsg) {
                cout << errorMsg << endl;
            }
        }
        code = "";
        input = "";
    }

}