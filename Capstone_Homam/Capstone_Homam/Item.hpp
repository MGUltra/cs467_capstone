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

using namespace std;

class Item
{
	private:
	string name;
	string description;
	string forensicAnalysis;

	public:
	//constructor
	Item(string, string, string);

	//get
	string getName();
	string getDescription();
	string getForensicAnalysis();

	//set
	void setName(string);
	void setDescription(string);
	void setForensicAnalysis(string);
};

#endif