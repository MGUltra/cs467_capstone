/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "Inventory.hpp"

/*******************************************************************************
*		CONTRUCTOR
*******************************************************************************/
Inventory::Inventory()
{
	// Blank Default Constructor
}

vector<string>* Inventory::getItemsFromInventory()
{
	return &itemsInInventory;
}

/*******************************************************************************
*		ADD FUNCTIONS
*******************************************************************************/
void Inventory::addItemToInventory(string newItem)
{
	itemsInInventory.push_back(newItem);
}

/*******************************************************************************
*		REMOVE FUNCTIONS
*******************************************************************************/
void Inventory::removeItemFromInventory(string removeThisItem)
{
	int index = findVectorIndex(removeThisItem, itemsInInventory);
	itemsInInventory.erase(itemsInInventory.begin() + index);
}

/*******************************************************************************
*		FIND VECTOR INDEX
*******************************************************************************/
int Inventory::findVectorIndex(string thisString, vector<string> thisVector)
{
	int size = thisVector.size();

	for (int i = 0; i <= size; i++)
	{
		if (thisString == thisVector[i])
		{
			return i;
		}
	}
}