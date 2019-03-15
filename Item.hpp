/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#ifndef ITEM_HPP
#define ITEM_HPP

/*------------------------------------------------------------------------------
		LIBRARIES
------------------------------------------------------------------------------*/
#include <iostream>
#include <string>

#include "Suspect.hpp"
#include "Notebook.hpp"

class Item
{
	private:
	std::string name;
	std::string displayName;      // display name of item
	std::string description;
	std::string forensicAnalysis;
	bool available;
	bool analyzed;
	bool usable;


	public:
	//constructor
	Item(std::string, std::string, std::string, bool);

	//get
	std::string getName();
	std::string getDisplayName();
	std::string getDescription();
	std::string getForensicAnalysis();
	bool getAvailable();
	bool getAnalyzed();
	bool getUseable();

	//set
	void setName(std::string);
	void setDisplayName(std::string);
	void setDescription(std::string);
	void setForensicAnalysis(std::string);
	void setAvailable(bool);
	void setAnalyzed(bool);
	void setUseable(bool);
	
	// actions
	
	void analyzeItem(Notebook*);
	
	void revealedByFeature(Notebook*);
	void revealedByHack(std::string, Notebook*);
	void revealedBySample(std::string, Notebook*);
	void revealedByItemUsed(std::string, std::string, Notebook*);
	void revealedByListen(Notebook*);
	
};

#endif