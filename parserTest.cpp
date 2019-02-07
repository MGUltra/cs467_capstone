#include <iostream>
#include <string>
#include <vector>

#include "word.hpp"
#include "verb.hpp"
#include "noun.hpp"
#include "parser.hpp"


int main()
{
	
	//create parser
	
	Parser* parser1 = new Parser();
	
	parser1->setVerbSet("this");
	parser1->setVerbSet("the");
	
	parser1->setNounSet("cat");
	parser1->setNounSet("is");
	parser1->setNounSet("message");
	parser1->setNounSet("new");
	
	
	parser1->newMessage("  This is, the new Message    ");
	
	parser1->printParsedStrings();
	
	parser1->printVerbNounGroupings();
	
	
	parser1->newMessage("  This is, the new Message    ");
	
	parser1->printParsedStrings();
	
	parser1->printVerbNounGroupings();
	
	/*
	parser1->newMessage("  This is,  next Message new new this this  ");
	
	parser1->printParsedStrings();
	
	parser1->printVerbNounGroupings();
	*/
	parser1->clearMessage();
	
	delete parser1;
	
	
}