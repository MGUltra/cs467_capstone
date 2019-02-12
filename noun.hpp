#ifndef NOUN_HPP
#define NOUN_HPP


#include "word.hpp"

class Noun: public Word
{	
	private:
	
	std::string wordText;
	
	Word* associatedVerb; 
	
	bool hasAVerb;
	
	
	public:
	
	// Constructor
	Noun();
		
	Noun(std::string, bool);
	
	Noun(std::string, bool, Word*);
	
	// Destructor
	~Noun();
	
	// Get Functions
	
	std::string virtual getText();
	
	// Set Functions
	
	void virtual setText(std::string);
	
	void setAssociatedVerb(Word*);
	
	void setHasAVerb(bool);
	
};



#endif