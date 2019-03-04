/*******************************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Rozalija Zibrat (Kendal Droddy, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has to interrogate
** suspects, investigate the crime scene, search for evidence, and ultimately
** decide who committed the murder.
*******************************************************************************/

#include "Feature.hpp"

/*******************************************************************************
*		CONTRUCTOR
*******************************************************************************/
Feature::Feature(std::string name, std::string description, std::string location, Item* itemAffected)
{
	setName(name);
	setDescription(description);
	setLocation(location);
	setItemAffected(itemAffected);
	alreadyInspected = false;
}

/*******************************************************************************
*		GET FUNCTIONS
*******************************************************************************/
std::string Feature::getName()
{
	return name;
}

std::string Feature::getDescriptionFirst()
{
	return descriptionFirst;
}

std::string Feature::getDescriptionAfter()
{
	return descriptionAfter;
}

std::string Feature::getLocation()
{
	return location;
}

bool Feature::getAlreadyInspected()
{
	return alreadyInspected;
}

bool Feature::getAlreadyActioned()
{
	return alreadyActioned;
}

bool Feature::getCanSample()
{
	return canSample;
}

bool Feature::getCanHack()
{
	return canHack;
}

bool Feature::actionAble()
{
	return alreadyInspected;
}

/*******************************************************************************
*		SET FUNCTIONS
*******************************************************************************/
void Feature::setName(std::string givenName)
{
	name = givenName;
}

void Feature::setLocation(std::string givenLocation)
{
	location = givenLocation;
}

void Feature::setAlreadyInspected(bool newBool)
{
	alreadyInspected = newBool;
}

void Feature::setItemAffected(Item* newItem)
{
	this->itemAffected = newItem;
}

void setAlreadyActioned()
{
	this->alreadyActioned = true;
}

void setCanSample(bool boolIn)
{
	this->canSample = boolIn;
}

void setCanHack(bool boolIn)
{
	this->canHack = boolIn;
}

void setActionAble(bool boolIn)
{
	this->actionAble = boolIn;
}


void Feature::inspected()
{
	
	this->itemAffected->revealedByFeature();
	
	this->setAlreadyInspected(true);
	
}