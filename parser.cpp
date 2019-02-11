
#include "parser.hpp"



/***************************************************************
***																													 ***
***                      Constructor                         ***
***																													 ***
****************************************************************/

Parser::Parser()
	: metaSet({"help"})
	, verbSet({"drop", "take", "inventory"})
	, nounSet({"north", "south", "east", "west"})
	, messageIn("")
	, parsedStrings()
	, gameActions()
	, numActions(0)
{

}
	

	
/***************************************************************
***																													 ***
***                      Destructor                          ***
***																													 ***
****************************************************************/

Parser::~Parser()
{
		
}
	

	
	
/***************************************************************
***																													 ***
***                      Get functions                       ***
***																													 ***
****************************************************************/

	
std::string Parser::getMessageIn()
{
	return this->messageIn;
}
	
std::string Parser::getParsedCurrentWord()
{
	return this->parsedStrings[0];
}
	
Word* Parser::getCurrentVerb()
{
	return this->gameActions[0];
}
	
std::vector<Word*>* Parser::getGameActions()
{
	return &gameActions;
}

int Parser::getNumActions()
{
	return this->numActions;
}
	
	
	
/***************************************************************
***																													 ***
***                      Set functions                       ***
***																													 ***
****************************************************************/



/***************************************************************
Function: setMessageIn

Parameter: Takes a string

Returns: none, but sets messageIn to cleaned string

Desc: 
This function takes the input string, calls to_lower and
trim from the boost library on a temp variable holding the string,
then sets the resulting string to the messageIn variable.

****************************************************************/	
void Parser::setMessageIn(std::string input)
{
		
	std::string tempString;
		
	tempString = input;
		
	// set all characters to lowercase
	boost::algorithm::to_lower(tempString);
		
	// remove any leading or trailing whitespace
	boost::algorithm::trim(tempString);
		
	this->messageIn = tempString;
}



/***************************************************************
Function: setNumActions

Parameter: one int

Returns: none, but sets the numActions variable

Desc: sets the numActions variable to the passed in value

****************************************************************/		
void Parser::setNumActions(int actions)
{
	this->numActions = actions;
}



/***************************************************************
Function: setMetaSet

Parameter: a single string

Returns: none

Desc: adds the passed in string to the metaSet unordered_set

****************************************************************/		
void Parser::setMetaSet(std::string newMeta)
{
	this->metaSet.insert(newMeta);
}



/***************************************************************
Function: setVerbSet

Parameter: a single string

Returns: none

Desc: adds the passed in string to the verbSet unordered_set

****************************************************************/		
void Parser::setVerbSet(std::string newVerb)
{
	this->verbSet.insert(newVerb);
}



/***************************************************************
Function: setNounSet

Parameter: a single string

Returns: none

Desc: adds the passed in string to the nounSet unordered_set

****************************************************************/		
void Parser::setNounSet(std::string newNoun)
{
	this->nounSet.insert(newNoun);
}




/***************************************************************
***																													 ***
***                      Other functions                     ***
***																													 ***
****************************************************************/


/***************************************************************
Function: newMessage

Parameter: 
takes a single string input.

Returns: 
none, but calls the setMessageIn method to set the param
string to that variable, and then calls the parser function.

Desc: 
This function calls clearMessage to delete older messages,
then calls setMessageIn with the parameter of this function as an 
argument and finally calls to parser function to process the 
new message.
****************************************************************/	
void Parser::newMessage(std::string newInput)
{
	/* TEST
	std::cout << std::endl;	
	std::cout << "Hello from newMessage" << std::endl;
	std::cout << std::endl;	
	*/
	
	// clear old message
		
	this->clearMessage();
		
	// call set message in
		
	this->setMessageIn(newInput);

		
	// call parserFunction
		
	this->parserFunction();
		
		
	// execute game commands?
	
	
	/* TEST
	std::cout << std::endl;	
	std::cout << "Goodbye from newMessage" << std::endl;
	std::cout << std::endl;
	*/
		
}


/***************************************************************
Function: parserFunction

Parameters: 
none, but requires newMessage to have been called to set the 
messageIn variable with a string to parse.Also accesses the unordered 
sets, so they need to be initialized

Returns: 
None, but sets the parsedStrings vector and calls the add methods
to add new words to the gameActions vector

Desc: 
This function first parses the messageIn variable string by
individual words and places them into the parsedStrings vector.

For each entry into the vector, the function will then test the word
for matching entries in the meta, verb, and noun unordered_sets and create
derived Word objects as appropriate while associating nouns and verbs that 
need to be executed together.

****************************************************************/
void Parser::parserFunction()
{
	Word* tempWord;
	
	//std::string messageIn = "examine baseball bat";
	//std::vector<std::string> parsedStrings;
	
	//boost::algorithm::split(this->parsedStrings, this->messageIn, [](char c){return c == ' ';});
	boost::algorithm::split(this->parsedStrings, this->messageIn, boost::is_any_of("\t,. "), boost::token_compress_on);
	
	
	
		
	// TODO: Create tests for first word Meta instructions 
	// for first word
			
			// test for meta
			// save/load/help/inventory
		
	
	// Iterate though all individual words stored in vector parsedStrings
	for (auto individualString : parsedStrings)
	{
		// TEST
		//std::cout << individualString << std::endl;
			

			
		// for each word
			
			
		// TODO
		// test for direction noun
				
			// if match - create noun without verb
			// or verb without noun ?
			// continue
				
				
				
		// test for verb
		if (this->verbSet.find(individualString) != this->verbSet.end())
		{
			// if match create new verb
			
			//TEST
			//std::cout << "Calling new" << std::endl;
			
			tempWord = new Verb(individualString);
				
			// call addVerb
			addVerb(tempWord);
					
					
			continue;
		}
				
				
				
		// test for noun
		if (this->nounSet.find(individualString) != this->nounSet.end())
		{
			// if game noun - create new noun
			
			//TEST
			//std::cout << "Calling new" << std::endl;
			
			tempWord = new Noun(individualString, true);
					
					
			// call addNounToVerb
			addNounToVerb(tempWord);
					
					
		}
		
		
		
		
	} // end of Iterate through parsedStrings loop


	
}



/***************************************************************
Function: addVerb

Parameter: a Word pointer

Returns: none

Desc: 
adds a verb to the gameactions vector and increments
the number of numActions

****************************************************************/ 
void Parser::addVerb(Word* newVerb)
{
	this->gameActions.push_back(newVerb);
	
	this->numActions++;
}
	
	
/***************************************************************
Function: addNounToVerb

Parameter: a Word pointer

Returns: none

Desc: 
calls the addNound function from Verb class in the current verb 
in gameActions vector to associate this noun with that verb object

****************************************************************/	
void Parser::addNounToVerb(Word* newNoun)
{
	this->gameActions[numActions-1]->addNoun(newNoun);
}

	
/***************************************************************
Function: executeMessage

Parameter: 

Returns: 

Desc:

****************************************************************/	
void Parser::executeMessage()
{
	
}



/***************************************************************
Function: clearMessage

Parameter: none

Returns: none

Desc: 
will delete all instantiated derived Word objects and erase
the vectors in the parser object.

****************************************************************/	
void Parser::clearMessage()
{
	for(int x = 0; x < this->numActions; x++)
	{
		
		((Verb*)gameActions[x])->deleteNouns();
		
		//TEST
		//std::cout << "Calling delete" << std::endl;
		
		delete gameActions[x];

	}
	
	this->parsedStrings.clear();
	
	this->gameActions.clear(); 
	
	this->messageIn = "";
	
	setNumActions(0);
}



/***************************************************************
***																													 ***
***                      TEST functions                      ***
***																													 ***
****************************************************************/
	
void Parser::printParsedStrings()
{
	for(int x = 0; x < this->parsedStrings.size(); x++)
	{
		std::cout << parsedStrings[x] << std::endl;
	}
}

void Parser::printVerbNounGroupings()
{
	for(int x = 0; x < this->numActions; x++)
	{
		
		std::cout << "Verb: " << gameActions[x]->getText() << " -> ";
		
		
		for(int y = 0; y < ((Verb*)gameActions[x])->getNumberOfNouns(); y++)
		{
			std::cout << "Noun: " << ((Verb*)gameActions[x])->getIndexNounText(y) << " -> ";
			
		}
		
		std::cout << "end" << std::endl;
	}
	
}

void Parser::printUnparsedString()
{
	std::cout << this->messageIn << std::endl;
}