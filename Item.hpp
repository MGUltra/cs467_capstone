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


class Item
{
	private:
	std::string name;
	std::string description;
	std::string forensicAnalysis;
	bool available;
	bool analyzed;
	bool usable;
	Suspect* belongsTo;

	public:
	//constructor
	Item(std::string, std::string, std::string, Suspect*, bool);

	//get
	std::string getName();
	std::string getDescription();
	std::string getForensicAnalysis();
	bool getAvailable();
	bool getAnalyzed();
	bool getUseable();
	Suspect* getBelongsTo();

	//set
	void setName(std::string);
	void setDescription(std::string);
	void setForensicAnalysis(std::string);
	void setAvailable(bool);
	void setAnalyzed(bool);
	bool setUseable(bool);
	void setBelongsTo(Suspect*);
	
	// actions
	
	void analyzeItem();
	
	void revealedByFeature();
	void revealedByHack(std::string);
	void revealedBySample(std::string);
	void revealedByItemUsed(std::string, std::string);
	
};

#endif