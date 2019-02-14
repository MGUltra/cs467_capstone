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


class Item
{
	private:
	std::string name;
	std::string description;
	std::string forensicAnalysis;
	bool available;
	bool analyzed;

	public:
	//constructor
	Item(std::string, std::string, std::string);

	//get
	std::string getName();
	std::string getDescription();
	std::string getForensicAnalysis();
	bool getAvailable();
	bool getAnalyzed();

	//set
	void setName(std::string);
	void setDescription(std::string);
	void setForensicAnalysis(std::string);
	void setAvailable(bool);
	void setAnalyzed(bool);
	
	// actions
	
	void revealedByFeature();
	
};

#endif