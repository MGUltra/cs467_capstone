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
	numItemsInInventory = 0;
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
	
	numItemsInInventory++;
}

/*******************************************************************************
*		REMOVE FUNCTIONS
*******************************************************************************/
void Inventory::removeItemFromInventory(string removeThisItem)
{
	int index = findVectorIndex(removeThisItem, itemsInInventory);
	itemsInInventory.erase(itemsInInventory.begin() + index);
	
	numItemsInInventory--;
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


/*******************************************************************************
*		PRINT CURRENT INVENTORY
*******************************************************************************/
void Inventory::printCurrentInventory()
{
	std::cout << "Current Inventory" << std::endl;
	std::cout << "-----------------" << std::endl;
	
	if(numItemsInInventory > 0)
	{
		for(auto i : itemsInInventory)
		{
			std::cout << "| " << i << std::endl;
		}
	}
	else
	{
		std::cout << "Inventory Empty" << std::endl;
	}
	std::cout << "-----------------" << std::endl;
	std::cout << std::endl;
}




