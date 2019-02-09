#include <iostream>
#include <string>
#include <vector>

#include "word.hpp"
#include "verb.hpp"
#include "noun.hpp"
#include "parser.hpp"


int main()
{

	// test variables
	int numOfNouns;
	int x;

	

	// create 2 verbs
	Verb* verb1 = new Verb("Verb1");
	Verb* verb2 = new Verb("Verb2");



	// create 3 nouns
	Noun* noun1 = new Noun("Noun1", false);
	Noun* noun2 = new Noun("Noun2", false);
	Noun* noun3 = new Noun("Noun3", false);



	// add noun to verb 1
	verb1->addNoun(noun1);


	// add 2 noun to verb 2
	verb2->addNoun(noun2);
	verb2->addNoun(noun3);

	//int numOfNouns;

	// ouput verb 1 contents
	numOfNouns = verb1->getNumberOfNouns();
	
	std::cout << "Verb 1: " << verb1->getText() << std::endl;
	
	for(x = 0; x < numOfNouns; x++)
	{
		std::cout << "Noun " << x+1 << ": " << verb1->getIndexNounText(x) << std::endl;
	}
	

	

	// output verb 2 contents
	
	numOfNouns = verb2->getNumberOfNouns();
	
	std::cout << "Verb 2: " << verb2->getText() << std::endl;
	
	for(x = 0; x < numOfNouns; x++)
	{
		std::cout << "Noun at index " << x << ": " << verb2->getIndexNounText(x) << std::endl;
	}

	
	// removing nouns from verbs
	
	std::cout << "Testing get first noun and remove first noun on verb 2" << std::endl;
	
	// display first noun

	std::cout << "First Noun: " << verb2->getFirstNounText() << std::endl;
	
	// remove first noun
	
	std::cout << "Removing first noun" << std::endl;
	
	verb2->removeNoun();
	
	// display first noun

	std::cout << "First Noun: " << verb2->getFirstNounText() << std::endl;

	// delete all

	delete verb1;
	delete verb2;

	delete noun1;
	delete noun2;
	delete noun3;


}