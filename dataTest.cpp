/******************************************************************
** Program: Capstone Project - Team Homam - W2019
** Author: Kendal Droddy (Rozalija Zibrat, Matthew Garner)
** Date: 17 March 2019
** Description: A murder mystery game where the player has 
** to interrogate suspects, investigate the crime scene, search 
** for evidence, and ultimately decide who committed the murder.
*******************************************************************/
#include "dataRead.hpp"
#include <iostream>
#include <fstream>

int main()
{
  int num = 0;
  std::ifstream inFile;
  std::string input;

  //Test window size
  int winFlag = calcWindowSize();
  if (winFlag == 0)
    return 0;

  //Switch for rooms
  while(num != -1)
  {
    //Test Menu
    inFile.open("testMenu.txt", std::ios::out);
    readFileDefault(inFile);
    inFile.close();
    std::cin >> num;
    switch(num)
    {
      case 1:
        inFile.open("roomText/cellLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/cellShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 2:
        inFile.open("roomText/policeStationLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/policeStationShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 3:
        inFile.open("roomText/labLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/labShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 4:
        inFile.open("roomText/carlsLivingRoomLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/carlsLivingRoomShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 5:
        inFile.open("roomText/carlsGarageLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/carlsGarageShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 6:
        inFile.open("roomText/carlsBathroomLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/carlsBathroomShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 7:
        inFile.open("roomText/carlsKitchenLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/carlsKitchenShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 8:
        inFile.open("roomText/dansKitchenLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/dansKitchenShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 9:
        inFile.open("roomText/dansLivingRoomLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/dansLivingRoomShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 10:
        inFile.open("roomText/dansBedroomLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/dansBedroomShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 11:
        inFile.open("roomText/dansPorchLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/dansPorchShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 12:
        inFile.open("roomText/vincesFoyerLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/vincesFoyerShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 13:
        inFile.open("roomText/vincesLivingRoomLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/vincesLivingRoomShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 14:
        inFile.open("roomText/vincesBedroomLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/vincesBedroomShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
      case 15:
        inFile.open("roomText/vincesOfficeLong.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        inFile.open("roomText/vincesOfficeShort.txt", std::ios::out);
        readFileDefault(inFile);
        inFile.close();
        break;
    } 
  }
  return 0;
}