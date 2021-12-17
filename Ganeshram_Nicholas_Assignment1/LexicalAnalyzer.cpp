#include <iostream>
#include <fstream>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

LexicalAnalyzer::LexicalAnalyzer(ifstream* scf) {
	sourceFile = scf;
	charPositionNumber = 0;
	filePoint = 0;
	currLexemmeNum = 1;
	start = true;
}

int LexicalAnalyzer::getcharPositionNumber() {
	return this->charPositionNumber;
}

Token* LexicalAnalyzer::getNextToken() {
	Token* t;
	t = new Token();
	string ss = "";
	TokenCodes tcode;
	if(start){ 
		this->sourceFile->getline(line, 100);
		start = false;
	}
	while (line[charPositionNumber] == ' ') 
	{
		charPositionNumber++;
	}
	if (line[charPositionNumber] == '\0') 
		{
		tcode = TokenCodes::NEWLINE;
		ss = '\n';
		this->sourceFile->ignore();
		if (this->sourceFile->peek() == EOF) { line[0] = EOI; 
		}
		else{ 
		this->sourceFile->getline(line, 100); 
		}
		charPositionNumber = 0;
	}
	else if (line[charPositionNumber] == EOI ||
		line[charPositionNumber] == EOF) 
		{
		tcode = TokenCodes::EOI;
		ss = EOF;
		charPositionNumber += 1;
	}
	else 
		{
		while (line[charPositionNumber] != ' '){
			if (line[charPositionNumber] == '\0') { break; }
			ss += line[charPositionNumber];
			charPositionNumber += 1;
		}
		charPositionNumber += 1;
		tcode = getTokenCode(ss);
	}
	if (tcode == TokenCodes::NAL) { ss = ""; 
	}
	if (tcode == TokenCodes::NEWLINE) { ss = "\\n"; 
	}
	t->setLexemeString(ss);
	t->setTokenCode(tcode);
	t->setLexemeNumber(currLexemmeNum);
	currLexemmeNum++;
	return t;
}


TokenCodes LexicalAnalyzer::getTokenCode(string ss) 
	{

	TokenCodes tcode;

	if (ss == "+") { tcode = TokenCodes::PLUS; 
	}
	
	else if (ss == "-") { tcode = TokenCodes::MINUS; 
	}
	
	else if (ss == "*") { tcode = TokenCodes::TIMES; 
	}
	
	else if (ss == "=") { tcode = TokenCodes::EQL; 
	}
	
	else if (ss == "(") { tcode = TokenCodes::LPAREN; 
	}
	
	else if (ss == ")") { tcode = TokenCodes::RPAREN; 
	}
	
	else if (ss == ",") { tcode = TokenCodes::COMMA; 
	}
	
	else if (ss == ";") { tcode = TokenCodes::SEMICOLON; 
	}
	
	else if (ss == "/") { tcode = TokenCodes::SLASH; 
	}
	
	else if (ss == "/=") { tcode = TokenCodes::NEQ; 
	}
	
	else if (ss == ":") { tcode = TokenCodes::COLON; 
	}
	
	else if (ss == ":=") { tcode = TokenCodes::BECOMES; 
	}
	
	else if (ss == "<") { tcode = TokenCodes::LSS; 
	}
	
	else if (ss == ">") { tcode = TokenCodes::GTR; 
	}
	
	else if (ss == "<=") { tcode = TokenCodes::LEQ; 
	}
	
	else if (ss == ">=") { tcode = TokenCodes::GEQ; 
	}
	
	else if (ss == "begin") { tcode = TokenCodes::BEGINSYM; 
	}
	
	else if (ss == "boolean") { tcode = TokenCodes::BOOLSYM; 
	}
	
	else if (ss == "else") { tcode = TokenCodes::ELSESYM; 
	}
	
	else if (ss == "end") { tcode = TokenCodes::ENDSYM; 
	}
	
	else if (ss == "false") { tcode = TokenCodes::FALSESYM; 
	}
	
	else if (ss == "get") { tcode = TokenCodes::GETSYM; 
	}
	
	else if (ss == "if") { tcode = TokenCodes::IFSYM; 
	}
	
	else if (ss == "is") { tcode = TokenCodes::ISSYM; 
	}
	
	else if (ss == "integer") { tcode = TokenCodes::INTSYM; 
	}
	
	else if (ss == "loop") { tcode = TokenCodes::LOOPSYM; 
	}
	
	else if (ss == "not") { tcode = TokenCodes::NOTSYM; 
	}
	
	else if (ss == "procedure") { tcode = TokenCodes::PROCSYM; 
	}
	
	else if (ss == "put") { tcode = TokenCodes::PUTSYM; 
	}
	
	else if (ss == "rem") { tcode = TokenCodes::REMSYM; 
	}
	
	else if (ss == "then") { tcode = TokenCodes::THENSYM; 
	}
	
	else if (ss == "true") { tcode = TokenCodes::TRUESYM; 
	}
	
	else if (ss == "while") { tcode = TokenCodes::WHILESYM; 
	}
	
	else if (ss == "then") { tcode = TokenCodes::MINUS; 
	}
	
	else if (ss == "null") { tcode = TokenCodes::NULLSYM;
	 }
	
	else if (checkIfIdentifier(ss)) { tcode = TokenCodes::IDENT; 
	}
	
	else if (checkIfNumeric(ss)) { tcode = TokenCodes::NUMLIT; 
	}
	
	else { tcode = TokenCodes::NAL; 
	}

	return tcode;
}

bool LexicalAnalyzer::checkIfIdentifier(string ss) {
	if (checkIfLetter(ss[0])) 
	{
		for (int i = 0; i < ss.size(); i++) {
			if (!checkIfDigit(ss[i]) && !checkIfLetter(ss[i])) 
				{
				return false;
			}
		}
	}
	else 
	{ 	
	return false; 
	}
	return true;
}

bool LexicalAnalyzer::checkIfDigit(char ch) 
	{
	if (ch >= '0' && ch <= '9') {
		return true;
	}
	return false;
}
bool LexicalAnalyzer::checkIfLetter(char ch) 
	{
	if (ch >= 'A' && ch <= 'Z') {
		return true;
	}
	if (ch >= 'a' && ch <= 'z') {
		return true;
	}
	return false;
}
bool LexicalAnalyzer::checkIfNumeric(string ss) 
	{
	for (int i = 0; i < ss.size(); i++) {
		if (!checkIfDigit(ss[i])) {
			return false;
		}
	}
	return true;
}