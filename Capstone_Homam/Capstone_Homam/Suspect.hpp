/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#ifndef SUSPECT_HPP
#define SUSPECT_HPP

/*------------------------------------------------------------------------------
LIBRARIES
------------------------------------------------------------------------------*/
#include <iostream>
#include <string>

using namespace std;

class Suspect
{
private:
	string name;
	string description;
	string answer1;
	string answer2;

public:
	//constructor
	Suspect(string, string, string, string);
	//destructor
	~Suspect();

	//get
	string getName();
	string getDescription();
	string getAnswer1();
	string getAnswer2();

	//set
	void setName(string);
	void setDescription(string);
	void setAnswer1(string);
	void setAnswer2(string);
};

#endif