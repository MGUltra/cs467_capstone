

#include "verb.hpp"


/***************************************************************
***																													 ***
***                      Constructors                        ***
***																													 ***
****************************************************************/
Verb::Verb()
{
	this->wordText = "";
	this->numberOfNouns = 0;
}
	
Verb::Verb(std::string input)
{
	this->wordText = input;
	this->numberOfNouns = 0;
}

	
/***************************************************************
***																													 ***
***                      Destructor                          ***
***																													 ***
****************************************************************/

Verb::~Verb()
{
	
}



/***************************************************************
***																													 ***
***                      Get functions                       ***
***																													 ***
****************************************************************/

std::string Verb::getText()
{
	return this->wordText;
}


Word* Verb::getFirstNounPointer()
{
	return this->associatedNouns.front();
}

std::string Verb::getFirstNounText()
{
	return this->associatedNouns[0]->getText();
}

std::string Verb::getIndexNounText(int index)
{
	if(index < this->numberOfNouns)
		return this->associatedNouns[index]->getText();
	else
		return "Error: no nound at index";
}

int Verb::getNumberOfNouns()
{
	return this->numberOfNouns;
}



/***************************************************************
***																													 ***
***                      Set functions                       ***
***																													 ***
****************************************************************/

void Verb::setText(std::string input)
{
	this->wordText = input;
}



/***************************************************************
***																													 ***
***                      Other functions                     ***
***																													 ***
****************************************************************/


/***************************************************************
Function: 

Parameters: 

Returns: 

Desc:

****************************************************************/
void Verb::addNoun(Word* newNoun)
{
	this->associatedNouns.push_back(newNoun);

	this->numberOfNouns++;
}


/***************************************************************
Function: 

Parameters: 

Returns: 

Desc:

****************************************************************/
void Verb::removeNoun()
{
	if(this->numberOfNouns > 0)
	{
		this->associatedNouns.erase(this->associatedNouns.begin());
		this->numberOfNouns--;
	}
}


/***************************************************************
Function: 

Parameters: 

Returns: 

Desc:

****************************************************************/
void Verb::deleteNouns()
{
	for(int x = 0; x < this->numberOfNouns; x++)
	{
		// TEST
		//std::cout << "Calling delete" << std::endl;
		
		delete this->associatedNouns[x];
	
	}
	
	this->associatedNouns.clear();
	
}
