#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>

#include "Token.h"
#include "TokenCodes.h"

class LexicalAnalyzer
{
private:
    ifstream* sourceFile;
    int charPositionNumber;
    int filePoint;
    int currLexemmeNum;
    char line[100];
    bool start;

public:
    LexicalAnalyzer(ifstream*);
    int getcharPositionNumber();
    Token* getNextToken();
    TokenCodes getTokenCode(string ss);
    bool checkIfIdentifier(string ss);
    bool checkIfNumeric(string ss);
    bool checkIfDigit(char ch);
    bool checkIfLetter(char ch);
};

#endif