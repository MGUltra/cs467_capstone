/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "Notebook.hpp"

/*******************************************************************************
*		CONTRUCTOR
*******************************************************************************/
Notebook::Notebook()
{
	
}


/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
std::string Notebook::getEntry(std::string name)
{
	return notebookEntries[name];
}


/*******************************************************************************
*		ADD FUNCTION
*******************************************************************************/
void Notebook::setEntry(std::string name, std::string entry)
{
	notebookEntries[name] = entry;
}


template <typename Archive>
void Notebook::serialize(Archive& ar, const unsigned int version)
{
	ar& notebookEntries;
}