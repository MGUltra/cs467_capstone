#ifndef VERB_HPP
#define VERB_HPP


#include "word.hpp"

class Verb: public Word
{
	private:
	
	std::string wordText;
	
	std::vector<Word*> associatedNouns; 
	
	int numberOfNouns;
	
	
	public:
	
	// Constructor
	Verb();
	
	Verb(std::string);
	
	// Destructor
	~Verb();
	
	// Get Functions
	
	std::string virtual getText();
	
	Word* getFirstNounPointer();
	
	std::string getFirstNounText();
	
	std::string getIndexNounText(int);
	
	int getNumberOfNouns();
	
	
	// Set Functions
	
	void virtual setText(std::string);
	
	
	// Other Functions
	
	void virtual addNoun(Word*);
	
	void removeNoun();
	
	void deleteNouns();
	
};



#endif