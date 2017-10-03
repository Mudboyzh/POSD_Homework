#ifndef TOKEN_H
#define TOKEN_H
#include <string> 
using std::string;

class Token {
public:
	virtual string symbol() = 0;
	virtual string value() = 0;	
	virtual bool match(Token &t) = 0;
	virtual string className() = 0;
};

#endif