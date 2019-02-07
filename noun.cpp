
#include "noun.hpp"

/***************************************************************
***																													 ***
***                      Constructors                        ***
***																													 ***
****************************************************************/

Noun::Noun()
{
	
}

Noun::Noun(std::string wordText, bool hasVerb)
{
	setText(wordText);
	setHasAVerb(hasVerb);
}

Noun::Noun(std::string wordText, bool hasVerb, Word* associatedVerb)
{
	setText(wordText);
	setHasAVerb(hasVerb);
	setAssociatedVerb(associatedVerb);
}



/***************************************************************
***																													 ***
***                      Destructor                          ***
***																													 ***
****************************************************************/

Noun::~Noun()
{
	
}



/***************************************************************
***																													 ***
***                      Get functions                       ***
***																													 ***
****************************************************************/

std::string Noun::getText()
{
	return this->wordText;
}
	
	

/***************************************************************
***																													 ***
***                      Set functions                       ***
***																													 ***
****************************************************************/

void Noun::setText(std::string newText)
{
	this->wordText = newText;
}

void Noun::setAssociatedVerb(Word* verbPointer)
{
	this->associatedVerb = verbPointer;
}
	
void Noun::setHasAVerb(bool boolValue)
{
	this->hasAVerb = boolValue;
}



/***************************************************************
***																													 ***
***                      Other functions                     ***
***																													 ***
****************************************************************/
