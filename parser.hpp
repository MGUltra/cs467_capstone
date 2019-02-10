
#ifndef PARSER_HPP
#define PARSER_HPP

/***************************************************************
***                      Libraries                           ***
****************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <boost/algorithm/string.hpp>

#include "word.hpp"
#include "verb.hpp"
#include "noun.hpp"
//#include "Player.hpp"
//#include "Victim.hpp"
//#include "Suspect.hpp"


/***************************************************************
***                        Class                             ***
****************************************************************/
class Parser
{
	
	private:
	
	std::unordered_set<std::string> metaSet;
	
	std::unordered_set<std::string> verbSet;
	
	std::unordered_set<std::string> nounSet;
	
	std::string messageIn;
	
	std::vector<std::string> parsedStrings;
	
	std::vector<Word*> gameActions; 
	
	// number of verbs or action nouns without verbs
	// note: number of calls to game functions may be higher than this number
	// since multiple nouns can be associated with a verb
	int numActions;
	
	//unordered_map<string, Item*> itemMap;
	//unordered_map<string, Room*> roomMap;
	//unordered_map<string, Feature*> featureMap;
	//unordered_map<string, Suspect*> suspectMap;
	
	public:
	
	// Constructor
	Parser();
	
	// Destructor
	~Parser();
	
	
	// Get Functions
	
	std::string getMessageIn();
		
	std::string getParsedCurrentWord();
	
	Word* getCurrentVerb();
	
	std::vector<Word*>* getGameActions();
	
	int getNumActions();
	
	
	// Set functions
	
	void setMessageIn(std::string);
	
	void setNumActions(int);
	
	void setMetaSet(std::string);
	
	void setVerbSet(std::string);
	
	void setNounSet(std::string);
	
	
	// Other Functions
	
	void newMessage(std::string);
	
	void parserFunction();
	
	void addVerb(Word*);
	
	void addNounToVerb(Word*);
	
	void executeMessage(); //TODO
	
	void clearMessage();

	
	
	// Test Functions
	
	void printParsedStrings();
	
	void printVerbNounGroupings(); 
	
	void printUnparsedString(); 

};

#endif