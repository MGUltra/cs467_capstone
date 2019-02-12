#include <iostream>
#include <string>
#include <vector>

#include "word.hpp"
#include "verb.hpp"
#include "noun.hpp"
#include "parser.hpp"

#define DEFAULT "\033[0m"
#define BLACK   "\033[30m" 
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m" 
#define RED     "\033[31m"    

int main()
{
	
	//create parser
	
	Parser* parser1 = new Parser();
	
	parser1->setVerbSet("drop");
	parser1->setVerbSet("take");
	
	parser1->setNounSet("controller");
	parser1->setNounSet("cigarette");
	parser1->setNounSet("photograph");
	parser1->setNounSet("taco");
	
	std::string inputMessage = "    Drop the cigarette, and then take the taco, photograph and controller     ";
	
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << RED << "Input string" << DEFAULT << std::endl;
	std::cout << RED << "-------------------------------------------------" << DEFAULT << std::endl;
	std::cout << YELLOW << inputMessage << DEFAULT << std::endl;
	
	std::cout << std::endl;
	
	parser1->newMessage(inputMessage);
	
	std::cout << std::endl;
	
	std::cout << RED << "input string after Boost library tolower and trim" << DEFAULT << std::endl;
	std::cout << RED << "-------------------------------------------------" << DEFAULT << std::endl;
	std::cout << YELLOW << parser1->getMessageIn() << DEFAULT << std::endl;
	
	std::cout << std::endl;
	
	std::cout << RED << "input string after being parsed by words" << DEFAULT << std::endl;
	std::cout << RED << "-------------------------------------------------" << DEFAULT << std::endl;
	parser1->printParsedStrings();
	
	std::cout << std::endl;
	
	std::cout << RED << "input string after being Grouped by Verb/Noun Associations" << DEFAULT << std::endl;
	std::cout << RED << "-------------------------------------------------" << DEFAULT << std::endl;
	
	parser1->printVerbNounGroupings();
	
	std::cout << std::endl;
	
	
	/*
	parser1->newMessage("  This is,  next Message new new this this  ");
	
	parser1->printParsedStrings();
	
	parser1->printVerbNounGroupings();
	*/
	parser1->clearMessage();
	
	delete parser1;
	
	
}