#ifndef WORD_HPP
#define WORD_HPP

#include <iostream>
#include <string>
#include <vector>


class Word
{
	private:
	
	std::string wordText;
	
	
	public:
	
	// Constructor
	Word();
	
	// Destructor
	~Word();
	
	// Virtual Functions
	void virtual setText();
	
	std::string virtual getText();
	
	void virtual addNoun(Word*);
	
};

#endif